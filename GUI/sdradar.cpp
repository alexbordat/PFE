// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// Title:    SDR_API for C++
//
// Author:   Ancortek Inc.
// Contact:  Michael.Jian@Ancortek.com
//
// Description:
//   The SDRadar class provide a simple and intuitive way to pull data from any
//   of Ancortek's software defined radios using LibUSB.
//
//   This program is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, version 3 of the License.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// Include Ancortek's SDR API
#include "sdradar.h"

// Public Class Constructor
SDRadar::SDRadar ()
{
    // Initialize LibUSB pointers to NULL
    sdr_context = NULL;
    sdr_handle = NULL;
}

// Public Class Destructor
SDRadar::~SDRadar ()
{
    // Release the LibUSB interface claimed for the handle
    if (sdr_handle)
        libusb_release_interface (sdr_handle, 0);

    // Close the SDR LibUSB device handle
    if (sdr_handle)
        libusb_close (sdr_handle);

    // Destroy the LibUSB context
    if (sdr_context)
        libusb_exit (sdr_context);

    // Restore handle and context to NULL
    sdr_handle = NULL;
    sdr_context = NULL;
}

// Public Method - Send radar parameters to device
void SDRadar::update_radar_parameters ()
{
    // Instantiate radar parameter updating instruction buffer
    unsigned char *instruction_buffer = new unsigned char[SDR_INSTRUCTION_COPIES];

    // Fill the instruction buffer
    for (int i = 0; i < SDR_INSTRUCTION_COPIES; i += 2)
        std::memcpy (instruction_buffer + i, &(Parameters.value), 2);

    // Keep track of the number of bytes transfered to the device
    int bytes_sent = 0;

    // Attempt a bulk data transfer from the device to the PC                                                                             ou from the PC to the device ??
    libusb_bulk_transfer (sdr_handle, SDR_ENDPOINT_TX, instruction_buffer, SDR_INSTRUCTION_COPIES, &bytes_sent, SDR_TIMEOUT_READ_DATA_MS);
}

// Public Method - Synchronous (blocking) request for data
// (Returns the number of bytes received)
int SDRadar::request_data_synchronous (
                                       unsigned int requested_bytes,
                                       unsigned char *buffer,
                                       unsigned int timrout_ms
                                       )
{
    // Keep track of the number of bytes attained from the device
    int bytes_attained = -1;

    // Attempt a bulk data transfer from the device to the PC
    libusb_bulk_transfer (sdr_handle, SDR_ENDPOINT_RX, buffer, requested_bytes, &bytes_attained, timrout_ms);

    // Return the number of bytes received
    return bytes_attained;
}

// Public Method - Obtain SDRadar model number
// (Returns int corresponding to "Public Enumeration - SDRadar Model Number")
int SDRadar::obtain_SDRadar_model_num(){

    // Instantiate SDRadar model number retrieving instruction
    unsigned char *instruction_buffer = new unsigned char[SDR_INSTRUCTION_COPIES];

    // Fill the instruction buffer
    uint16_t src = 0x1f3f;
    for (int i = 0; i < SDR_INSTRUCTION_COPIES; i += 2)
        std::memcpy (instruction_buffer + i, &(src), 2);

    // Keep track of the number of bytes transfered to the device
    int bytes_sent = 0;

    // Attempt a bulk data transfer from the device to the PC
    libusb_bulk_transfer (sdr_handle, SDR_ENDPOINT_TX, instruction_buffer, SDR_INSTRUCTION_COPIES, &bytes_sent, SDR_TIMEOUT_READ_DATA_MS);

    // Instantiate a buffer for retrieving SDRadar model information
    unsigned char *SDRadar_num_buffer_char = new unsigned char[USB_BUFFER_LEFTOVER+2048];

    // Keep track of the number of bytes attained from the device
    int bytes_attained = -1;

    // Attempt a bulk data transfer from the device to the PC
    libusb_bulk_transfer (sdr_handle, SDR_ENDPOINT_RX, SDRadar_num_buffer_char, USB_BUFFER_LEFTOVER+2048, &bytes_attained, SDR_TIMEOUT_READ_INFINITE);

    int SDR_model_num = SDRadar_num_buffer_char[4098] | SDRadar_num_buffer_char[4097] << 8;

    // Clean up
    delete[] instruction_buffer;

    // Return
    return SDR_model_num;
}


// Public Method - Obtain SDRadar model
// (Returns int corresponding to "Public Enumeration - SDRadar Model Number")
uint32_t SDRadar::obtain_SDRadar_model(){

    // Instantiate SDRadar model number retrieving instruction
    unsigned char *instruction_buffer = new unsigned char[SDR_INSTRUCTION_COPIES];

    // Fill the instruction buffer
    uint16_t src = 0x1f3f;
    for (int i = 0; i < SDR_INSTRUCTION_COPIES; i += 2)
        std::memcpy (instruction_buffer + i, &(src), 2);

    // Keep track of the number of bytes transfered to the device
    int bytes_sent = 0;

    // Attempt a bulk data transfer from the device to the PC
    libusb_bulk_transfer (sdr_handle, SDR_ENDPOINT_TX, instruction_buffer, SDR_INSTRUCTION_COPIES, &bytes_sent, SDR_TIMEOUT_READ_DATA_MS);

    // Instantiate a buffer for retrieving SDRadar model information
    unsigned char *SDRadar_num_buffer_char = new unsigned char[USB_BUFFER_LEFTOVER+2048];

    // Keep track of the number of bytes attained from the device
    int bytes_attained = -1;

    // Attempt a bulk data transfer from the device to the PC
    libusb_bulk_transfer (sdr_handle, SDR_ENDPOINT_RX, SDRadar_num_buffer_char, USB_BUFFER_LEFTOVER+2048, &bytes_attained, SDR_TIMEOUT_READ_INFINITE);

    uint32_t* SDRadar_num_buffer_uint32 = reinterpret_cast<uint32_t*>(SDRadar_num_buffer_char);

    uint32_t SDRadar_model = SDRadar_num_buffer_uint32[1023];

    if ((SDRadar_model & 0xF0000000) == 0xE0000000){
        // switching two bytes
            uint32_t temp1 = (SDRadar_model >> 16);
            uint32_t temp2 = (SDRadar_model << 16);
            uint32_t* temp_p = &SDRadar_model;
            *temp_p = temp1 | temp2;
    }


//    uint32_t SDRadar_model = 0xffffeeee;

//    if ( (SDRadar_num_buffer_char[4099] & 0xF0) == 0xF0)
//        SDRadar_model = SDRadar_num_buffer_char[4099] | SDRadar_num_buffer_char[4098] << 8 | SDRadar_num_buffer_char[4100] << 16 | SDRadar_num_buffer_char[4101] << 24;
//    else if ( (SDRadar_num_buffer_char[4099] & 0xE0) == 0xE0)
//        SDRadar_model = SDRadar_num_buffer_char[4101] | SDRadar_num_buffer_char[4100] << 8 | SDRadar_num_buffer_char[4102] << 16 | SDRadar_num_buffer_char[4103] << 24;


    // Clean up
    delete[] instruction_buffer;
    delete[] SDRadar_num_buffer_char;

    // Return
    return SDRadar_model;
}


// Public Method - Send radar bandwidth parameters to device
// Output - Tramp: Actural ramp-up time
double SDRadar::bandwidth_parameters_udpate(double Freq_start, double Freq_stop, double sweeptime, int sdr_model_num){

    // Initialize FMCW Sawtooth PLL registries
    uint32_t *Reg_01 = new uint32_t;
    uint32_t *Reg_02 = new uint32_t;
    uint32_t *Reg_03 = new uint32_t;
    uint32_t *Reg_04 = new uint32_t;
    uint32_t *Reg_05 = new uint32_t;
    uint32_t *Sweep_N = new uint32_t;

    // PLL registries calculation
    double Tramp;
    if (sdr_model_num == SDRadar::SDRadar_2400AD4 || sdr_model_num == SDRadar::SDRadar_2400AD2 || sdr_model_num == SDRadar::SDRadar_2400T2R4)
        Tramp = FMCW_PLL_registry_calculation_div16(Freq_start, Freq_stop, sweeptime, Reg_01, Reg_02, Reg_03, Reg_04, Reg_05, Sweep_N);
    else if (sdr_model_num == SDRadar::SDRadar_240AD)
        Tramp = FMCW_PLL_registry_calculation(Freq_start, Freq_stop, sweeptime, Reg_01, Reg_02, Reg_03, Reg_04, Reg_05, Sweep_N);
    else
        Tramp = FMCW_PLL_registry_calculation_div2(Freq_start, Freq_stop, sweeptime, Reg_01, Reg_02, Reg_03, Reg_04, Reg_05, Sweep_N);

    // Divide the registry instruction into high/low byte
    u_Start_freq_int.bytes.high = (*Reg_01 >> 4*3) ;
    u_Start_freq_int.bytes.low = *Reg_01 ;
    u_Start_freq_frac.bytes.high = (*Reg_02 >> 4*3) ;
    u_Start_freq_frac.bytes.low = *Reg_02 ;
    u_Sweepstop_N.bytes.high = (*Sweep_N >> 4*3);
    u_Sweepstop_N.bytes.low = (*Sweep_N);
    u_Freq_step.bytes.high = (*Reg_03 >> 4*3) ;
    u_Freq_step.bytes.low = *Reg_03 ;
    u_Stop_freq_int.bytes.high = (*Reg_04 >> 4*3) ;
    u_Stop_freq_int.bytes.low = *Reg_04 ;
    u_Stop_freq_frac.bytes.high = (*Reg_05 >> 4*3) ;
    u_Stop_freq_frac.bytes.low = *Reg_05;


    // PLL settings insctruction for forwarding
    // Note: Each instruction has to be sent one by one!!! Cannot combine them and send them at once!!!
    unsigned char *instruction_buffer = new unsigned char[SDR_INSTRUCTION_COPIES];
    int bytes_sent;

    for (int i = 0; i < SDR_INSTRUCTION_COPIES; i += 2)
        std::memcpy (instruction_buffer + i, &u_Sweepstop_N.instruct.high, 2);
    // Attempt a bulk data transfer from the device to the PC
    libusb_bulk_transfer (sdr_handle, SDR_ENDPOINT_TX, instruction_buffer, SDR_INSTRUCTION_COPIES, &bytes_sent, SDR_TIMEOUT_READ_DATA_MS);

    for (int i = 0; i < SDR_INSTRUCTION_COPIES; i += 2)
        std::memcpy (instruction_buffer + i, &u_Sweepstop_N.instruct.low, 2);
    // Attempt a bulk data transfer from the device to the PC
    libusb_bulk_transfer (sdr_handle, SDR_ENDPOINT_TX, instruction_buffer, SDR_INSTRUCTION_COPIES, &bytes_sent, SDR_TIMEOUT_READ_DATA_MS);

    for (int i = 0; i < SDR_INSTRUCTION_COPIES; i += 2)
        std::memcpy (instruction_buffer + i, &u_Freq_step.instruct.high, 2);
    // Attempt a bulk data transfer from the device to the PC
    libusb_bulk_transfer (sdr_handle, SDR_ENDPOINT_TX, instruction_buffer, SDR_INSTRUCTION_COPIES, &bytes_sent, SDR_TIMEOUT_READ_DATA_MS);


    for (int i = 0; i < SDR_INSTRUCTION_COPIES; i += 2)
        std::memcpy (instruction_buffer + i, &u_Freq_step.instruct.low, 2);
    // Attempt a bulk data transfer from the device to the PC
    libusb_bulk_transfer (sdr_handle, SDR_ENDPOINT_TX, instruction_buffer, SDR_INSTRUCTION_COPIES, &bytes_sent, SDR_TIMEOUT_READ_DATA_MS);


    for (int i = 0; i < SDR_INSTRUCTION_COPIES; i += 2)
        std::memcpy (instruction_buffer + i, &u_Stop_freq_int.instruct.high, 2);
    // Attempt a bulk data transfer from the device to the PC
    libusb_bulk_transfer (sdr_handle, SDR_ENDPOINT_TX, instruction_buffer, SDR_INSTRUCTION_COPIES, &bytes_sent, SDR_TIMEOUT_READ_DATA_MS);


    for (int i = 0; i < SDR_INSTRUCTION_COPIES; i += 2)
        std::memcpy (instruction_buffer + i, &u_Stop_freq_int.instruct.low, 2);
    // Attempt a bulk data transfer from the device to the PC
    libusb_bulk_transfer (sdr_handle, SDR_ENDPOINT_TX, instruction_buffer, SDR_INSTRUCTION_COPIES, &bytes_sent, SDR_TIMEOUT_READ_DATA_MS);


    for (int i = 0; i < SDR_INSTRUCTION_COPIES; i += 2)
        std::memcpy (instruction_buffer + i, &u_Stop_freq_frac.instruct.high, 2);
    // Attempt a bulk data transfer from the device to the PC
    libusb_bulk_transfer (sdr_handle, SDR_ENDPOINT_TX, instruction_buffer, SDR_INSTRUCTION_COPIES, &bytes_sent, SDR_TIMEOUT_READ_DATA_MS);


    for (int i = 0; i < SDR_INSTRUCTION_COPIES; i += 2)
        std::memcpy (instruction_buffer + i, &u_Stop_freq_frac.instruct.low, 2);
    // Attempt a bulk data transfer from the device to the PC
    libusb_bulk_transfer (sdr_handle, SDR_ENDPOINT_TX, instruction_buffer, SDR_INSTRUCTION_COPIES, &bytes_sent, SDR_TIMEOUT_READ_DATA_MS);


    for (int i = 0; i < SDR_INSTRUCTION_COPIES; i += 2)
        std::memcpy (instruction_buffer + i, &u_Start_freq_int.instruct.high, 2);
    // Attempt a bulk data transfer from the device to the PC
    libusb_bulk_transfer (sdr_handle, SDR_ENDPOINT_TX, instruction_buffer, SDR_INSTRUCTION_COPIES, &bytes_sent, SDR_TIMEOUT_READ_DATA_MS);


    for (int i = 0; i < SDR_INSTRUCTION_COPIES; i += 2)
        std::memcpy (instruction_buffer + i, &u_Start_freq_int.instruct.low, 2);
    // Attempt a bulk data transfer from the device to the PC
    libusb_bulk_transfer (sdr_handle, SDR_ENDPOINT_TX, instruction_buffer, SDR_INSTRUCTION_COPIES, &bytes_sent, SDR_TIMEOUT_READ_DATA_MS);


    for (int i = 0; i < SDR_INSTRUCTION_COPIES; i += 2)
        std::memcpy (instruction_buffer + i, &u_Start_freq_frac.instruct.high, 2);
    // Attempt a bulk data transfer from the device to the PC
    libusb_bulk_transfer (sdr_handle, SDR_ENDPOINT_TX, instruction_buffer, SDR_INSTRUCTION_COPIES, &bytes_sent, SDR_TIMEOUT_READ_DATA_MS);


    for (int i = 0; i < SDR_INSTRUCTION_COPIES; i += 2)  // PLL instruction end flag
        std::memcpy (instruction_buffer + i, &u_Start_freq_frac.instruct.low, 2);
    // Attempt a bulk data transfer from the device to the PC
    libusb_bulk_transfer (sdr_handle, SDR_ENDPOINT_TX, instruction_buffer, SDR_INSTRUCTION_COPIES, &bytes_sent, SDR_TIMEOUT_READ_DATA_MS);


    // Clean up
    delete[] instruction_buffer;
    delete Reg_01;
    delete Reg_02;
    delete Reg_03;
    delete Reg_04;
    delete Reg_05;
    delete Sweep_N;

    return Tramp;
}

// Public Method - FMCW PLL Registry Calculation
// Input - Freq_start: Starting frequency in Hz
//          Freq_stop: Stopping frequency in Hz
//          sweeptime: Sweep time in second
// Output - Tramp: Actural ramp-up time
double SDRadar::FMCW_PLL_registry_calculation(double Freq_start, double Freq_stop, double
    sweeptime, uint32_t *Reg_01, uint32_t *Reg_02, uint32_t *Reg_03, uint32_t *Reg_04,
    uint32_t *Reg_05, uint32_t *Sweep_N)
{
    double Tramp = 0;
    double T_downchirp;
    double Tramp_percent;
    double Start_N;
    double Stop_N;
    uint32_t Start_N_int;
    uint32_t max_sweepover;
    double N_Step_Size_desired;
    uint32_t Frac_N_Step_Size;
    double Nbr_of_Steps;
    uint32_t Nbr_of_Big_Steps;

    if ( Parameters.options.modulation == SDRadar::MD_Sawtooth){

        if (sweeptime == 125e-6){
            T_downchirp = 5e-6;
            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
            Tramp = sweeptime*Tramp_percent;
            max_sweepover = 1024;
            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
        } else if (sweeptime == 250e-6){
            T_downchirp = 5e-6;
            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
            Tramp = sweeptime*Tramp_percent;
            max_sweepover = 2048;
            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
        } else if (sweeptime == 500e-6){
            T_downchirp = 70e-6;
            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
            Tramp = sweeptime*Tramp_percent;
            max_sweepover = 4096;
            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
        } else if (sweeptime == 1e-3 ){
            T_downchirp = 90e-6;
            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
            Tramp = sweeptime*Tramp_percent;
            max_sweepover = 8192;
            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
        } else if (sweeptime == 2e-3) {
            T_downchirp = 90e-6;
            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
            Tramp = sweeptime*Tramp_percent;
            max_sweepover = 16384;
            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
        } else if (sweeptime == 4e-3) {
            T_downchirp = 90e-6;
            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
            Tramp = sweeptime*Tramp_percent;
            max_sweepover = 32768;
            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
        } else if (sweeptime == 8e-3){
            T_downchirp = 90e-6;
            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
            Tramp = sweeptime*Tramp_percent;
            max_sweepover = 65536;
            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
        }

    } else if (Parameters.options.modulation == SDRadar::MD_Triangle){

        Tramp = sweeptime/2*0.9;

    }


    Start_N = Freq_start / 5.0E+7;
    Stop_N = Freq_stop / 5.0E+7;
    Start_N_int= std::floor(Start_N);
    *Reg_01 = Start_N_int;
    *Reg_02 = std::round((Start_N - *Reg_01) * 1.6777216E+7);

    Nbr_of_Steps = Tramp / (1/50E6);
    N_Step_Size_desired = (Stop_N - Start_N) / Nbr_of_Steps;
    Frac_N_Step_Size = std::round(N_Step_Size_desired * 1.6777216E+7);
    *Reg_03 = Frac_N_Step_Size;

    Nbr_of_Steps = std::round((Stop_N - Start_N) / (Frac_N_Step_Size / 1.6777216E+7));
    Nbr_of_Big_Steps = std::floor(Nbr_of_Steps*Frac_N_Step_Size/1.6777216E+7);
    *Reg_04 = Start_N_int + Nbr_of_Big_Steps;
    *Reg_05 = Nbr_of_Steps*Frac_N_Step_Size - std::floor(Nbr_of_Steps*Frac_N_Step_Size/1.6777216E+7)*1.6777216E+7 + *Reg_02;

    if (*Reg_05 > 1.6777216E+7) {
        (*Reg_04)++;
        *Reg_05 -= 1.6777216E+7;
    }

    return Tramp;
}


// Public Method - FMCW PLL Registry Calculation
// Input - Freq_start: Starting frequency in Hz
//          Freq_stop: Stopping frequency in Hz
//          sweeptime: Sweep time in second
// Output - Tramp: Actural ramp-up time
double SDRadar::FMCW_PLL_registry_calculation_div2(double Freq_start, double Freq_stop, double
    sweeptime, uint32_t *Reg_01, uint32_t *Reg_02, uint32_t *Reg_03, uint32_t *Reg_04,
    uint32_t *Reg_05, uint32_t *Sweep_N)
{
    double Tramp = 0;
    double T_downchirp;
    double Tramp_percent;
    double Start_N;
    double Stop_N;
    uint32_t Start_N_int;
    uint32_t max_sweepover;
    double N_Step_Size_desired;
    uint32_t Frac_N_Step_Size;
    double Nbr_of_Steps;
    uint32_t Nbr_of_Big_Steps;

    if ( Parameters.options.modulation == SDRadar::MD_Sawtooth){

        if (sweeptime == 125e-6){
            T_downchirp = 5e-6;
            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
            Tramp = sweeptime*Tramp_percent;
            max_sweepover = 1024;
            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
        } else if (sweeptime == 250e-6){
            T_downchirp = 5e-6;
            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
            Tramp = sweeptime*Tramp_percent;
            max_sweepover = 2048;
            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
        } else if (sweeptime == 500e-6){
            T_downchirp = 70e-6;
            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
            Tramp = sweeptime*Tramp_percent;
            max_sweepover = 4096;
            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
        } else if (sweeptime == 1e-3 ){
            T_downchirp = 90e-6;
            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
            Tramp = sweeptime*Tramp_percent;
            max_sweepover = 8192;
            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
        } else if (sweeptime == 2e-3) {
            T_downchirp = 90e-6;
            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
            Tramp = sweeptime*Tramp_percent;
            max_sweepover = 16384;
            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
        } else if (sweeptime == 4e-3) {
            T_downchirp = 90e-6;
            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
            Tramp = sweeptime*Tramp_percent;
            max_sweepover = 32768;
            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
        } else if (sweeptime == 8e-3){
            T_downchirp = 90e-6;
            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
            Tramp = sweeptime*Tramp_percent;
            max_sweepover = 65536;
            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
        }

//        if (sweeptime == 500e-6){
//            T_downchirp = 100e-6;
//            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
//            Tramp = sweeptime*Tramp_percent;
//            max_sweepover = 4096;
//            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
//        } else if (sweeptime == 1e-3 ){
//            T_downchirp = 160e-6;
//            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
//            Tramp = sweeptime*Tramp_percent;
//            max_sweepover = 4096;
//            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
//        } else if (sweeptime == 2e-3) {
//            T_downchirp = 180e-6;
//            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
//            Tramp = sweeptime*Tramp_percent;
//            max_sweepover = 4096;
//            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
//        } else if (sweeptime == 4e-3) {
//            T_downchirp = 180e-6;
//            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
//            Tramp = sweeptime*Tramp_percent;
//            max_sweepover = 4096;
//            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
//        } else if (sweeptime == 10e-3){
//            T_downchirp = 200e-6;
//            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
//            Tramp = sweeptime*Tramp_percent;
//            max_sweepover = 4096;
//            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
//        }

    } else if (Parameters.options.modulation == SDRadar::MD_Triangle){

        Tramp = sweeptime/2*0.9;

    }


    Start_N = Freq_start / 2.0 / 5.0E+7;
    Stop_N = Freq_stop / 2.0 / 5.0E+7;
    Start_N_int= std::floor(Start_N);
    *Reg_01 = Start_N_int;
    *Reg_02 = std::round((Start_N - *Reg_01) * 1.6777216E+7);

    Nbr_of_Steps = Tramp / (1/50E6);
    N_Step_Size_desired = (Stop_N - Start_N) / Nbr_of_Steps;
    Frac_N_Step_Size = std::round(N_Step_Size_desired * 1.6777216E+7);
    *Reg_03 = Frac_N_Step_Size;

    Nbr_of_Steps = std::round((Stop_N - Start_N) / (Frac_N_Step_Size / 1.6777216E+7));
    Nbr_of_Big_Steps = std::floor(Nbr_of_Steps*Frac_N_Step_Size/1.6777216E+7);
    *Reg_04 = Start_N_int + Nbr_of_Big_Steps;
    *Reg_05 = Nbr_of_Steps*Frac_N_Step_Size - std::floor(Nbr_of_Steps*Frac_N_Step_Size/1.6777216E+7)*1.6777216E+7 + *Reg_02;

    if (*Reg_05 > 1.6777216E+7) {
        (*Reg_04)++;
        *Reg_05 -= 1.6777216E+7;
    }

    return Tramp;
}



// Public Method - FMCW PLL Registry Calculation
// Input - Freq_start: Starting frequency in Hz
//          Freq_stop: Stopping frequency in Hz
//          sweeptime: Sweep time in second
// Output - Tramp: Actural ramp-up time
double SDRadar::FMCW_PLL_registry_calculation_div16(double Freq_start, double Freq_stop, double
    sweeptime, uint32_t *Reg_01, uint32_t *Reg_02, uint32_t *Reg_03, uint32_t *Reg_04,
    uint32_t *Reg_05, uint32_t *Sweep_N)
{
    double Tramp = 0;
    double T_downchirp;
    double Tramp_percent;
    double Start_N;
    double Stop_N;
    uint32_t Start_N_int;
    uint32_t max_sweepover;
    double N_Step_Size_desired;
    uint32_t Frac_N_Step_Size;
    double Nbr_of_Steps;
    uint32_t Nbr_of_Big_Steps;

    if ( Parameters.options.modulation == SDRadar::MD_Sawtooth){

        if (sweeptime == 125e-6){
            T_downchirp = 5e-6;
            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
            Tramp = sweeptime*Tramp_percent;
            max_sweepover = 1024;
            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
        } else if (sweeptime == 250e-6){
            T_downchirp = 5e-6;
            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
            Tramp = sweeptime*Tramp_percent;
            max_sweepover = 2048;
            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
        } else if (sweeptime == 500e-6){
            T_downchirp = 70e-6;
            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
            Tramp = sweeptime*Tramp_percent;
            max_sweepover = 4096;
            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
        } else if (sweeptime == 1e-3 ){
            T_downchirp = 90e-6;
            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
            Tramp = sweeptime*Tramp_percent;
            max_sweepover = 8192;
            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
        } else if (sweeptime == 2e-3) {
            T_downchirp = 90e-6;
            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
            Tramp = sweeptime*Tramp_percent;
            max_sweepover = 16384;
            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
        } else if (sweeptime == 4e-3) {
            T_downchirp = 90e-6;
            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
            Tramp = sweeptime*Tramp_percent;
            max_sweepover = 32768;
            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
        } else if (sweeptime == 8e-3){
            T_downchirp = 90e-6;
            Tramp_percent = 1 - T_downchirp*1.5/sweeptime;
            Tramp = sweeptime*Tramp_percent;
            max_sweepover = 65536;
            *Sweep_N = std::ceil(max_sweepover * (Tramp_percent + 0.01));
        }

    } else if (Parameters.options.modulation == SDRadar::MD_Triangle){

        Tramp = sweeptime/2*0.9;

    }


    Start_N = Freq_start / 16.0 / 5.0E+7;
    Stop_N = Freq_stop / 16.0 / 5.0E+7;
    Start_N_int= std::floor(Start_N);
    *Reg_01 = Start_N_int;
    *Reg_02 = std::round((Start_N - *Reg_01) * 1.6777216E+7);

    Nbr_of_Steps = Tramp / (1/50E6);
    N_Step_Size_desired = (Stop_N - Start_N) / Nbr_of_Steps;
    Frac_N_Step_Size = std::round(N_Step_Size_desired * 1.6777216E+7);
    *Reg_03 = Frac_N_Step_Size;

    Nbr_of_Steps = std::round((Stop_N - Start_N) / (Frac_N_Step_Size / 1.6777216E+7));
    Nbr_of_Big_Steps = std::floor(Nbr_of_Steps*Frac_N_Step_Size/1.6777216E+7);
    *Reg_04 = Start_N_int + Nbr_of_Big_Steps;
    *Reg_05 = Nbr_of_Steps*Frac_N_Step_Size - std::floor(Nbr_of_Steps*Frac_N_Step_Size/1.6777216E+7)*1.6777216E+7 + *Reg_02;

    if (*Reg_05 > 1.6777216E+7) {
        (*Reg_04)++;
        *Reg_05 -= 1.6777216E+7;
    }

    return Tramp;
}

// Private Method - Initialize LibUSB Device
int SDRadar::initialize ()
{
    // Throw an error if we encounter any problems
    try
    {
        // Initialize LibUSB
        if (libusb_init (&sdr_context) != LIBUSB_SUCCESS)
            // throw std::runtime_error ("Error: Could not initialize LibUSB.");
            throw LIBUSB_INIT_FAILED;

        // Open the device matching our SDR's VID and PID
        sdr_handle = libusb_open_device_with_vid_pid (sdr_context, SDR_USB_VID, SDR_USB_PID);
        if (!sdr_handle)
            // throw std::runtime_error ("Error: LibUSB could not find a matching VID/PID or an error was encountered.");
            throw VID_PID_MATCHING_FAILED;

        // Read the current value of the CPUCS register
        unsigned char reset_char;
        if (libusb_control_transfer (sdr_handle, 0xc0, 0xa0, 0xe600, 0, &reset_char, 1, SDR_TIMEOUT_DEVICE_RESET_MS) != 1)
            // throw std::runtime_error ("Error: Could not read the CPUCS register.");
            throw READ_CPUCS_FAILED;

        // Place the device into reset
        reset_char = reset_char | 0x01;
        if (libusb_control_transfer (sdr_handle, 0x40, 0xa0, 0xe600, 0, &reset_char, 1, SDR_TIMEOUT_DEVICE_RESET_MS) != 1)
            // throw std::runtime_error ("Error: Could not bring the device into reset mode.");
            throw IN_RESET_MODE_FAILED;

        // Sleep for 100ms (wait for device to enter reset)
        std::this_thread::sleep_for (std::chrono::milliseconds (100));

        // Cypress FX2LP USB Firmware
        // [0] Length of data to write
        // [2] Address start of write
        // [4] Start of data to write
        unsigned char firmware[15][21] = {
            {0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0xB8, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x0C, 0x00, 0xB8, 0x00, 0x78, 0x7F, 0xE4, 0xF6, 0xD8, 0xFD, 0x75, 0x81, 0x07, 0x02, 0x00, 0x03, 0x94, 0x00, 0x00, 0x00, 0x00},
            {0x10, 0x00, 0x03, 0x00, 0x90, 0xE6, 0x00, 0x74, 0x12, 0xF0, 0x00, 0x00, 0x00, 0xA3, 0x74, 0xCB, 0xF0, 0x00, 0x00, 0x00, 0x2F},
            {0x10, 0x00, 0x13, 0x00, 0x90, 0xE6, 0x0B, 0x74, 0x01, 0xF0, 0x00, 0x00, 0x00, 0x90, 0xE6, 0x12, 0x74, 0xA2, 0xF0, 0x00, 0x69},
            {0x10, 0x00, 0x23, 0x00, 0x00, 0x00, 0x90, 0xE6, 0x14, 0x74, 0xE0, 0xF0, 0x00, 0x00, 0x00, 0xE4, 0x90, 0xE6, 0x13, 0xF0, 0xA2},
            {0x10, 0x00, 0x33, 0x00, 0x00, 0x00, 0x00, 0x90, 0xE6, 0x15, 0xF0, 0x00, 0x00, 0x00, 0x90, 0xE6, 0x04, 0x74, 0x80, 0xF0, 0xE4},
            {0x10, 0x00, 0x43, 0x00, 0x00, 0x00, 0x00, 0x74, 0x82, 0xF0, 0x00, 0x00, 0x00, 0x74, 0x84, 0xF0, 0x00, 0x00, 0x00, 0x74, 0x6B},
            {0x10, 0x00, 0x53, 0x00, 0x86, 0xF0, 0x00, 0x00, 0x00, 0x74, 0x88, 0xF0, 0x00, 0x00, 0x00, 0xE4, 0xF0, 0x00, 0x00, 0x00, 0x67},
            {0x10, 0x00, 0x63, 0x00, 0x90, 0xE6, 0x1A, 0x74, 0x0D, 0xF0, 0x00, 0x00, 0x00, 0x90, 0xE6, 0x18, 0x74, 0x01, 0xF0, 0x00, 0x99},
            {0x10, 0x00, 0x73, 0x00, 0x00, 0x00, 0x74, 0x11, 0xF0, 0x00, 0x00, 0x00, 0xE4, 0x90, 0xE6, 0x09, 0xF0, 0x00, 0x00, 0x00, 0xB5},
            {0x10, 0x00, 0x83, 0x00, 0x90, 0xE6, 0x02, 0x74, 0xE0, 0xF0, 0x00, 0x00, 0x00, 0xA3, 0x74, 0x08, 0xF0, 0x00, 0x00, 0x00, 0xA2},
            {0x10, 0x00, 0x93, 0x00, 0x90, 0xE6, 0x24, 0x74, 0x02, 0xF0, 0x00, 0x00, 0x00, 0xE4, 0xA3, 0xF0, 0x00, 0x00, 0x00, 0x90, 0x56},
            {0x10, 0x00, 0xA3, 0x00, 0xE6, 0x34, 0x74, 0x80, 0xF0, 0x00, 0x00, 0x00, 0xE4, 0xA3, 0xF0, 0x90, 0xE6, 0x70, 0x74, 0x40, 0x3E},
            {0x05, 0x00, 0xB3, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x22, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x00, 0x00, 0x00, 0x01, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
        };

        // Declare the number firmware rows
        const int firmware_rows = 15;

        // Iterate through each row of our firmware
        for (int row = 0; row < firmware_rows; row++)
        {
            // Determine the length (in bytes) to write
            unsigned int write_length = firmware[row][0];

            // Ensure the write_length is greater than zero
            if (write_length > 0)
            {
                // Determine the address to start writing
                unsigned int write_address = firmware[row][2];

                // Transfer firmware to the device
                if (libusb_control_transfer (sdr_handle, 0x40, 0xa0, write_address, 0, firmware[row] + 4, write_length, SDR_TIMEOUT_FIRMWARE_WRITE_MS) != write_length)
                    // throw std::runtime_error ("Error: Firmware did not write the desired number of bytes.");
                    throw FIRMWARE_WRITTING_FAILED;
            }
        }

        // Bring the device out of the reset state
        reset_char = reset_char & 0xFE;
        if (libusb_control_transfer (sdr_handle, 0x40, 0xa0, 0xe600, 0, &reset_char, 1, SDR_TIMEOUT_DEVICE_RESET_MS) != 1)
            // throw std::runtime_error ("Error: Could not bring the device out of reset mode.");
            throw OUT_RESET_MODE_FAILED;

        // Sleep for 100ms (wait for device to come out of reset and re-enumerate)
        std::this_thread::sleep_for (std::chrono::milliseconds (500));

        // Release the LibUSB interface claimed for the handle
        if (sdr_handle) libusb_release_interface (sdr_handle, 0);

        // Close the SDR LibUSB device handle
        if (sdr_handle) libusb_close (sdr_handle);

        // Open the device matching the updated VID and PID
        sdr_handle = libusb_open_device_with_vid_pid (sdr_context, SDR_USB_VID, SDR_USB_PID);
        if (!sdr_handle)
            // throw std::runtime_error ("Error: LibUSB could not find a matching VID/PID or an error was encountered.");
            throw VID_PID_MATCHING_FAILED;

        // Claim the USB Interface
        if (libusb_claim_interface (sdr_handle, 0) != LIBUSB_SUCCESS)
            // throw std::runtime_error ("Error: Could not claim interface 0.");
            throw CLAIM_INTERFACE_0_FAILED;

        // Set alternate interface
        if (libusb_set_interface_alt_setting (sdr_handle, 0, 1) != LIBUSB_SUCCESS)
            // throw std::runtime_error ("Error: Could not set interface 0 to alternate setting (1).");
            throw INTERFACE_ALTERNATE_SETTING_FAILED;

        return SDRADAR_INIT_SUCCEED;
    }

    // Catch and report any error encountered
     catch ( SDRadar_Interface_Status e)
    {
        // Release the LibUSB interface claimed for the handle
        if (sdr_handle) libusb_release_interface (sdr_handle, 0);

        // Close the SDR LibUSB device handle
        if (sdr_handle) libusb_close (sdr_handle);

        // Destroy the LibUSB context
        if (sdr_context) libusb_exit (sdr_context);

        // Restore handle and context to NULL
        sdr_handle = NULL;
        sdr_context = NULL;

        // Return Error Code
        return e;
    }
}



