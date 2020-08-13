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
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// Standard Includes
#include <chrono>
#include <thread>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <cstring>
#include <cmath>

// Include LibUSB
#include "libusb.h"

// Setup Cypress VID/PID
#define SDR_USB_VID 0x04b4
#define SDR_USB_PID 0x8613

// Setup LibUSB Endpoints
#define SDR_ENDPOINT_RX 0x86                    // Endpoint - Device to PC
#define SDR_ENDPOINT_TX 0x02                    // Endpoint - PC to Device

// Define Timeouts
#define SDR_TIMEOUT_FIRMWARE_WRITE_MS 1000      // Firmware write timeout
#define SDR_TIMEOUT_DEVICE_RESET_MS 1000        // Device reset timeout
#define SDR_TIMEOUT_READ_DATA_MS 1000           // Read data from device timeout
#define SDR_TIMEOUT_READ_INFINITE 0             // Read data infinetely

// Define Sample Skip Counts
#define USB_BUFFER_LEFTOVER 4096
#define SDR_PEAK_SEARCH_HEAD 4096

// LibUSB Transfer Lengths
#define SDR_INSTRUCTION_COPIES 4096

// Ancortek SDR Interface Class
class SDRadar
{
public:

    // Public Class Constructor
    SDRadar ( );

    // Public Class Destructor
    ~SDRadar ( );

    // Public Enumeration - Operation Modes for Ancortek's general radar kits
    enum Parameter_Options : uint16_t
    {
        RX_CH_1 = 1, // 1 receiving channel
        RX_CH_2 = 2, // 2 receiving channels
        RX_CH_4 = 4, // 4 receiving channels
        TX_CH_1 = 1, // 1 transmitting channel
        TX_CH_2 = 2, // 2 transmitting channel
        SN_max = 0, // Max sampling number
        SN_half = 1, // 1/2 sampling number
        SN_quarter = 2, // 1/4 sampling number
        SN_one_eighth = 3, // 1/8 sampling number
        ST_125_us = 0, // Sweep time = 125 us
        ST_250_us = 1, // Sweep time = 250 us
        ST_500_us = 2, // Sweep time = 500 us
        ST_1_ms = 3, // Sweep time = 1 ms
        ST_2_ms = 4, // Sweep time = 2 ms
        ST_4_ms = 5, // Sweep time = 4 ms
        ST_8_ms = 6, // Sweep time = 8 ms
        MD_Sawtooth = 0, // FMCW sawtooth
        MD_Triangle = 1, // FMCW triangle
        MD_FSK = 2, // FSK
        MD_CW = 3 // CW
    };

    // Public Method - Initialize LibUSB Device
    int initialize( );

    // Public Method - Send radar parameters to device
    void update_radar_parameters ( );

    // Public Method - Synchronous (blocking) request for data
    // (Returns the number of bytes received)
    int request_data_synchronous (
                                   unsigned int requested_bytes,
                                   unsigned char *buffer,
                                   unsigned int timrout_ms = SDR_TIMEOUT_READ_DATA_MS
                                   );   

    // Public Method - Obtain SDRadar model number
    int obtain_SDRadar_model_num();

    // Public Method - Obtain SDRadar model
    uint32_t obtain_SDRadar_model();

    // Public Method - FMCW PLL registry calculation
    double FMCW_PLL_registry_calculation(double Freq_start, double Freq_stop, double sweeptime, uint32_t *Reg_01, uint32_t *Reg_02, uint32_t *Reg_03, uint32_t *Reg_04, uint32_t *Reg_05, uint32_t *Sweep_N);
    double FMCW_PLL_registry_calculation_div2(double Freq_start, double Freq_stop, double sweeptime, uint32_t *Reg_01, uint32_t *Reg_02, uint32_t *Reg_03, uint32_t *Reg_04, uint32_t *Reg_05, uint32_t *Sweep_N);
    double FMCW_PLL_registry_calculation_div16(double Freq_start, double Freq_stop, double sweeptime, uint32_t *Reg_01, uint32_t *Reg_02, uint32_t *Reg_03, uint32_t *Reg_04, uint32_t *Reg_05, uint32_t *Sweep_N);

    // Public Method - Send radar bandwidth parameters to device
    double bandwidth_parameters_udpate(double Freq_start, double Freq_stop, double sweeptime, int sdr_model_num);

    // Public Members - Radar Operating Parameters Firmware Values
    union SDR_Parameters
    {
        // Individual Option Access
        struct
        {
            uint16_t modulation : 3;
            uint16_t sweep_time : 4;
            uint16_t sampling_number : 2;
            uint16_t channel : 3;
            uint16_t header : 4;
        } options;

        // High/Low Byte Access
        struct
        {
            uint16_t low : 8;
            uint16_t high : 8;
        } bytes;

        // Full 16-bit Access
        uint16_t value;
    }; //Parameters = {.options = { 0, 0, 0, 0, 0xf } }; // Union initializer for GCC

    SDR_Parameters Parameters = {{0, 0, 0, 0, 0xf}}; // Uinion initializer for MSVC 2015

    // PLL settings
    union Start_Freq_Int{
        struct {
            uint16_t high ;
            uint16_t low ;
        }instruct;

        struct {
            uint16_t high : 12;
            uint16_t low : 12;
        }bytes;

    }; //u_Start_freq_int = {.instruct = {0x2000, 0x3000}};

    Start_Freq_Int u_Start_freq_int = {{0x2000, 0x3000}};

    union Start_Freq_Frac{
        struct {
            uint16_t high ;
            uint16_t low ;
        }instruct;

        struct {
            uint16_t high : 12;
            uint16_t low : 12;
        }bytes;

    }; //u_Start_freq_frac = {.instruct = {0x4000, 0x5000}};

    Start_Freq_Frac u_Start_freq_frac = {{0x4000, 0x5000}};

    union Sweepstop_N{
        struct {
            uint16_t high;
            uint16_t low;
        }instruct;

        struct {
            uint16_t high : 12;
            uint16_t low : 12;
        }bytes;

    }; //u_Sweepstop_N = {.instruct = {0x7000, 0x8000}};

    Sweepstop_N u_Sweepstop_N = {{0x7000, 0x8000}};

    union Freq_Step{
        struct {
            uint16_t high ;//= 0xD000;
            uint16_t low ;//= 0xE000;
        }instruct;

        struct {
            uint16_t high : 12;
            uint16_t low : 12;
        }bytes;

    }; //u_Freq_step = {.instruct = {0x9000, 0xa000}};

    Freq_Step u_Freq_step = {{0x9000, 0xa000}};

    union Stop_Freq_Int{
        struct {
            uint16_t high ;//= 0xD000;
            uint16_t low ;//= 0xE000;
        }instruct;

        struct {
            uint16_t high : 12;
            uint16_t low : 12;
        }bytes;

    }; //u_Stop_freq_int = {.instruct = {0xB000, 0xC000}};

    Stop_Freq_Int u_Stop_freq_int = {{0xb000, 0xc000}};

    union Stop_Freq_Frac{
        struct {
            uint16_t high ;//= 0xD000;
            uint16_t low ;//= 0xE000;
        }instruct;

        struct {
            uint16_t high : 12;
            uint16_t low : 12;
        }bytes;

    }; //u_Stop_freq_frac = {.instruct = {0xD000, 0xE000}};

    Stop_Freq_Frac u_Stop_freq_frac = {{0xd000, 0xe000}};


    // Public Enumeration - SDRadar Interface Status
    enum SDRadar_Interface_Status : int
    {
        SDRADAR_INIT_SUCCEED = 0,
        LIBUSB_INIT_FAILED = -1,
        VID_PID_MATCHING_FAILED = -2,
        READ_CPUCS_FAILED = -3,
        IN_RESET_MODE_FAILED = -4,
        FIRMWARE_WRITTING_FAILED = -5,
        OUT_RESET_MODE_FAILED = -6,
        CLAIM_INTERFACE_0_FAILED = -7,
        INTERFACE_ALTERNATE_SETTING_FAILED = -8
    };

    // Public Enumeration - SDRadar Model
    enum SDRadar_Model_Number
    {
        SDRadar_240AD = 0xF018E101,
        SDRadar_580AD = 0xF03AE101,
        SDRadar_580AD2 = 0xF03AE102,
        SDRadar_980AD = 0xF062E101,
        SDRadar_980AD2 = 0xF062E102,
        SDRadar_2400AD = 0xF0F0E101,
        SDRadar_2400AD2 = 0xF0F0E102,
        SDRadar_2400AD4 = 0xF0F0E104,
        SDRadar_2400T2R4 = 0xF0F0E204,
        SDRadar_NOT_RECOGNIZE = 0xFFFFEEEE
    };

// private:
    // LibUSB Context
    libusb_context *sdr_context;

    // LibUSB Device Handle
    libusb_device_handle *sdr_handle;

    // if LibUSB reference released?
    // boolean libusb_released;
};

