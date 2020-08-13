#include "MaFenetre.h"

MaFenetre::MaFenetre() : QWidget()
{

    init_done = false;
    updateRadar_done = false;
    updateBandwith_done = false;

    layoutPrincipal = new QVBoxLayout;
    layout_button = new QHBoxLayout;
    formLayout_radar = new QFormLayout;
    formLayout_bandwith = new QFormLayout;

    label_radar = new QLabel("<strong>Radar Parameter :</strong>");
    label_Bandwith = new QLabel("<strong>Bandwith Parameter :</strong>");

    desiredSeconds_box = new QSpinBox;
    modulationScheme_box = new QComboBox;
    numberOfChannel_box = new QComboBox;
    sweepTime_box = new QComboBox;
    samplingPerSweep_box = new QComboBox;
    freqStart_box = new QDoubleSpinBox;
    freqStop_box = new QDoubleSpinBox;

    desiredSeconds_box->setRange(1,100);
    desiredSeconds_box->setSuffix(" Seconde");

    freqStart_box->setRange(9.2,10.2);
    freqStart_box->setSuffix(" Ghz");

    freqStop_box->setRange(9.2,10.2);
    freqStop_box->setSuffix(" Ghz");

    modulationScheme_box-> addItem("MD_Sawtooth",QVariant(SDRadar::MD_Sawtooth));//SDRadar::MD_Sawtooth (0)
    modulationScheme_box-> addItem("MD_Triangle",QVariant(1));//SDRadar::MD_Triangle (1)
    modulationScheme_box-> addItem("MD_FSK",QVariant(SDRadar::MD_Triangle));//SDRadar::MD_FSK (2)
    modulationScheme_box-> addItem("MD_CW",QVariant(SDRadar::MD_CW));//SDRadar::MD_CW (3)

    numberOfChannel_box->addItem("1",QVariant(SDRadar::RX_CH_1));//SDRadar::RX_CH_1 (1)
    numberOfChannel_box->addItem("2",QVariant(SDRadar::RX_CH_2));//SDRadar::RX_CH_2 (2)
    numberOfChannel_box->addItem("4",QVariant(SDRadar::RX_CH_4));//SDRadar::RX_CH_4 (4)

    sweepTime_box->addItem("125_us",QVariant(SDRadar::ST_125_us));//SDRadar::ST_125_us (0)
    sweepTime_box->addItem("250_us",QVariant(SDRadar::ST_250_us));//SDRadar::ST_250_us (1)
    sweepTime_box->addItem("500_us",QVariant(SDRadar::ST_500_us));//SDRadar::ST_500_us (2)
    sweepTime_box->addItem("1_ms",QVariant(SDRadar::ST_1_ms));//SDRadar::ST_1_ms (3)
    sweepTime_box->addItem("2_ms",QVariant(SDRadar::ST_2_ms));//SDRadar::ST_2_ms (4)
    sweepTime_box->addItem("4_ms",QVariant(SDRadar::ST_4_ms));//SDRadar::ST_4_ms (5)
    sweepTime_box->addItem("8_ms",QVariant(SDRadar::ST_8_ms));//SDRadar::ST_8_ms (6)

    samplingPerSweep_box-> addItem("SN_max",QVariant(SDRadar::SN_max));//SDRadar::SN_max (0)
    samplingPerSweep_box-> addItem("SN_half",QVariant(SDRadar::SN_half));//SDRadar::SN_half (1)
    samplingPerSweep_box-> addItem("SN_quarter",QVariant(SDRadar::SN_quarter));//SDRadar::SN_quarter (2)
    samplingPerSweep_box-> addItem("SN_one_eighth",QVariant(SDRadar::SN_one_eighth));//SDRadar::SN_one_eighth (3)

    formLayout_radar->addRow("Nombre de seconde désirée :", desiredSeconds_box);
    formLayout_radar->addRow("Schéma de modulation :", modulationScheme_box);
    formLayout_radar->addRow("Nombre de Receiving Channel :", numberOfChannel_box);
    formLayout_radar->addRow("Sweep Time :", sweepTime_box);
    formLayout_radar->addRow("Number of sample per sweep :", samplingPerSweep_box);


    formLayout_bandwith->addRow("Start Frequency :", freqStart_box);
    formLayout_bandwith->addRow("Stop Frequency :", freqStop_box);

    m_bouton_initialize = new QPushButton("Initialize the Radar");
    m_bouton_update_radar = new QPushButton("Update Radar");
    m_bouton_update_bandwith = new QPushButton("Update Bandwith");
    m_bouton_request_data = new QPushButton("Request Data");
    m_bouton_process_data = new QPushButton("Process Data");

    layout_button->addWidget(m_bouton_initialize);
    layout_button->addWidget(m_bouton_update_radar);
    layout_button->addWidget(m_bouton_update_bandwith);
    layout_button->addWidget(m_bouton_request_data);
    layout_button->addWidget(m_bouton_process_data);

    layoutPrincipal->addWidget(label_radar);
    layoutPrincipal->addLayout(formLayout_radar);
    layoutPrincipal->addWidget(label_Bandwith);
    layoutPrincipal->addLayout(formLayout_bandwith);
    layoutPrincipal->addLayout(layout_button);

    setLayout(layoutPrincipal);

    QObject::connect(m_bouton_initialize, SIGNAL(clicked()), this, SLOT(initializeRadar()));
    QObject::connect(m_bouton_update_radar, SIGNAL(clicked()), this, SLOT(updateRadar()));
    QObject::connect(m_bouton_update_bandwith, SIGNAL(clicked()), this, SLOT(updateBandwith()));
    QObject::connect(m_bouton_request_data, SIGNAL(clicked()), this, SLOT(requestData()));
    QObject::connect(m_bouton_process_data, SIGNAL(clicked()), this, SLOT(processData()));



    sdr = new SDRadar ();

}

MaFenetre::~MaFenetre()
{
    delete sdr;
    delete fenetreRecap;
}

void MaFenetre::initializeRadar()
{
    return_code_init = sdr->initialize();
    switch (return_code_init)
    {
    case SDRadar::SDRADAR_INIT_SUCCEED:
//        std::cout << "Initialization Succeeded. " << std::endl;
    {
        SDRadar_model_num = sdr->obtain_SDRadar_model();
        QString SDRadar_model_string("");
        switch (SDRadar_model_num)
        {
        case SDRadar::SDRadar_240AD:
//            std::cout << "SDR-KIT 240AD" << std::endl;
            SDRadar_model_string = QString("SDR-KIT 240AD ");
            break;
        case SDRadar::SDRadar_580AD:
//            std::cout << "SDR-KIT 580AD" << std::endl;
            SDRadar_model_string = QString("SDR-KIT 580AD ");
            break;
        case SDRadar::SDRadar_580AD2:
//            std::cout << "SDR-KIT 580AD2" << std::endl;
            SDRadar_model_string = QString("SDR-KIT 580AD2 ");
            break;
        case SDRadar::SDRadar_980AD:
//            std::cout << "SDR-KIT 980AD" << std::endl;
            SDRadar_model_string = QString("SDRadar_980AD ");
            break;
        case SDRadar::SDRadar_980AD2:
//            std::cout << "SDR-KIT 980AD2" << std::endl;
            SDRadar_model_string = QString("SDR-KIT 980AD2 ");
            break;
        case SDRadar::SDRadar_2400AD:
//            std::cout << "SDR-KIT 2400AD" << std::endl;
            SDRadar_model_string = QString("SDRadar_2400AD ");
            break;
        case SDRadar::SDRadar_2400AD2:
//            std::cout << "SDR-KIT 2400AD2" << std::endl;
            SDRadar_model_string = QString("SDRadar_2400AD2 ");
            break;
        case SDRadar::SDRadar_2400AD4:
//            std::cout << "SDR-KIT 2400AD4" << std::endl;
            SDRadar_model_string = QString("SDRadar_2400AD4 ");
            break;
        case SDRadar::SDRadar_2400T2R4:
//            std::cout << "SDR-KIT 2400T2R4" << std::endl;
            SDRadar_model_string = QString("SDRadar_2400T2R4 ");
            break;
        default:
//            std::cout << "Device Not Recognized" << std::endl;
            SDRadar_model_string = QString("Device Not Recognized ");
            break;
        }
        QMessageBox::information(this, "Initialization", "Initialization Succeeded, Model : " + SDRadar_model_string);
        init_done = true;
    }
        break; // End of the success case.

    case SDRadar::LIBUSB_INIT_FAILED:
//        std::cout << "Error: LibUSB could not find a matching VID/PID or an error was encountered." << std::endl;
        QMessageBox::critical(this, "Initialization", "Error: LibUSB could not find a matching VID/PID or an error was encountered.");
        break;
    case SDRadar::VID_PID_MATCHING_FAILED:
//        std::cout << "Error: LibUSB could not find a matching VID/PID or an error was encountered." << std::endl;
        QMessageBox::critical(this, "Initialization", "Error: LibUSB could not find a matching VID/PID or an error was encountered.");
        break;
    case SDRadar::READ_CPUCS_FAILED:
//        std::cout << "Error: Could not read the CPUCS register." << std::endl;
        QMessageBox::critical(this, "Initialization", "Error: Could not read the CPUCS register.");
        break;
    case SDRadar::IN_RESET_MODE_FAILED:
//        std::cout << "Error: Could not bring the device into reset mode." << std::endl;
        QMessageBox::critical(this, "Initialization", "Error: Could not bring the device into reset mode.");
        break;
    case SDRadar::FIRMWARE_WRITTING_FAILED:
//        std::cout << "Error: Firmware did not write the desired number of bytes." << std::endl;
        QMessageBox::critical(this, "Initialization", "Error: Firmware did not write the desired number of bytes.");
        break;
    case SDRadar::OUT_RESET_MODE_FAILED:
//        std::cout << "Error: Could not bring the device out of reset mode." << std::endl;
        QMessageBox::critical(this, "Initialization", "Error: Could not bring the device out of reset mode.");
        break;
    case SDRadar::CLAIM_INTERFACE_0_FAILED:
//        std::cout << "Error: Could not claim interface 0." << std::endl;
        QMessageBox::critical(this, "Initialization", "Error: Could not claim interface 0.");
        break;
    case SDRadar::INTERFACE_ALTERNATE_SETTING_FAILED:
//        std::cout << "Error: Could not set interface 0 to alternate setting (1)." << std::endl;
        QMessageBox::critical(this,"Initialization", "Error: Could not set interface 0 to alternate setting (1).");
        break;
    }
}

void MaFenetre::updateRadar()
{
    if(init_done)
    {
        desiredSeconds=desiredSeconds_box->value();
        int index_modulationScheme = (modulationScheme_box->currentData()).toInt();
        numberOfChannel = (numberOfChannel_box->currentData()).toInt();
        int numberOfSamplePerSweep = (samplingPerSweep_box->currentData()).toInt();
        sweepTime_index =(sweepTime_box->currentData()).toInt();

        switch (sweepTime_index) {
        case SDRadar::ST_125_us:
            sweepTime = 125.0e-6;
            break;
        case SDRadar::ST_250_us:
            sweepTime = 250.0e-6;
            break;
        case SDRadar::ST_500_us:
            sweepTime = 500.0e-6;
            break;
        case SDRadar::ST_1_ms:
            sweepTime = 1.0e-3;
            break;
        case SDRadar::ST_2_ms:
            sweepTime = 2.0e-3;
            break;
        case SDRadar::ST_4_ms:
            sweepTime = 4.0e-3;
            break;
        case SDRadar::ST_8_ms:
            sweepTime = 8.0e-3;
            break;
        }

        NTS_max = max_data_rate * sweepTime / numberOfChannel;
        switch (numberOfSamplePerSweep) {
        case SDRadar::SN_max:
            NTS = NTS_max;
            break;
        case SDRadar::SN_half:
            NTS = NTS_max * 0.5;
            break;
        case SDRadar::SN_quarter:
            NTS = NTS_max * 0.25;
            break;
        case SDRadar::SN_one_eighth:
            NTS = NTS_max * 0.125;
            break;
        }

        sdr->Parameters.options.modulation = index_modulationScheme;
        sdr->Parameters.options.channel = numberOfChannel;
        sdr->Parameters.options.sweep_time = sweepTime_index;
        sdr->Parameters.options.sampling_number = numberOfSamplePerSweep;

        sdr->update_radar_parameters();
        QMessageBox::information(this, "Update Radar", "Update radar done !");
        updateRadar_done = true;
    }
    else
    {
        QMessageBox::information(this, "Update Radar", "You must first initialize the Radar");
    }

}

void MaFenetre::updateBandwith()
{ 
    if(init_done &&  updateRadar_done)
    {
        freqStart = freqStart_box->value();//Enlever le double lorsque je décomenterai le *.h
        freqStop = freqStop_box->value();//Enlever le double lorsque je décomenterai le *.h

        double threshold = 0.0;

        freqStart*=1e9;
        freqStop*=1e9;

        switch (sweepTime_index) {
        case 0:
            threshold= 0.1e9;
            break;
        case 1:
            threshold= 0.2e9;
            break;
        case 2:
            threshold= 0.4e9;
            break;
        case 3:
            threshold= 0.4e9;
            break;
        case 4:
            threshold= 0.5e9;
            break;
        case 5:
            threshold= 0.6e9;
            break;
        case 6:
            threshold= 1.0e9;
            break;
        }

        if( (freqStop-freqStart <= threshold) && (freqStart <= freqStop))
        {
            sdr->bandwidth_parameters_udpate(freqStart, freqStop, sweepTime, SDRadar_model_num);
            QMessageBox::information(this, "Update Bandwith", "Update bandwith done !");
            updateBandwith_done = true;
        }
        else
        {
            QMessageBox::information(this, "Update Bandwith", "The bandwith is too large for the selected Sweep time and Frequence stop must be higher than Frequence Start");
        }

    }
    else
    {
        QMessageBox::information(this, "Update Bandwith", "You must first initialize the Radar and Update its parameter");
    }
}

void MaFenetre::requestData()
{
    if(init_done &&  updateRadar_done && updateBandwith_done)
    {
//        fenetreRecord = new QDialog;
//        layoutRecord = new QVBoxLayout;
//        labelRecord = new QLabel;
//        labelRecord->setText("Recording ...");
//        layoutRecord->addWidget(labelRecord);

//        fenetreRecord->setLayout(layoutRecord);

        unsigned long buffer_size = (std::ceil(NTS / sweepTime * desiredSeconds /512 )) * 512 * 2 * 2 * numberOfChannel + USB_BUFFER_LEFTOVER;

        // Create a buffer to hold our received samples
        buffer_char = new unsigned char[buffer_size];

//        fenetreRecord->open();
        std::cout << "Recording..." << std::endl;

//         Request data from the device
        int bytes_received = sdr->request_data_synchronous (buffer_size, buffer_char, SDR_TIMEOUT_READ_INFINITE);

//        delete fenetreRecord;

        // Convert to uint16_t samples (as SHORT)
        uint16_t *buffer_uint16 = reinterpret_cast<uint16_t*> (buffer_char);

        // Create a file header buffer to store radar parameters info
        uint16_t header_buffer[6];
        header_buffer[0] = sdr->Parameters.options.modulation;
        header_buffer[1] = sdr->Parameters.options.channel;
        header_buffer[2] = static_cast<uint16_t> (freqStart / 1e6); // in MHz
        header_buffer[3] = static_cast<uint16_t> (freqStop / 1e6); // in MHz
        header_buffer[4] = static_cast<uint16_t> (sweepTime * 1e6); // in micro-second
        header_buffer[5] = (uint16_t) NTS;

        QString fichier = QFileDialog::getSaveFileName(this,"Enregistrer un fichier",QString());//
        QByteArray nomFichier = fichier.toLocal8Bit();
        const char *addr_nomFichier = nomFichier.data();




        // Start an output file
        FILE *file = std::fopen (addr_nomFichier, "wb");//addr_nomFichier ou "./sdr_kit_980AD2_data.bin"

        // Write the header buffer to a file
        std::fwrite (header_buffer, sizeof (*header_buffer), 6, file);

        // Determine the number of uint16 values to write to the output file
        size_t write_count = (bytes_received - USB_BUFFER_LEFTOVER)/2;

        // Write the buffer to a file
        std::fwrite (buffer_uint16 + USB_BUFFER_LEFTOVER/2, sizeof (*buffer_uint16), write_count, file);

        // Close our file handle
        std::fclose (file);



        delete buffer_char;

//         Print out the radar parameters
//        if (sdr->Parameters.options.modulation == SDRadar::MD_Sawtooth){
//            std::cout << "Modulation scheme: FMCW Sawtooth" << std::endl;
//        }else if (sdr->Parameters.options.modulation == SDRadar::MD_CW){
//            std::cout << "Modulation scheme: CW" << std::endl;
//        };

        fenetreRecap = new QDialog;
        layoutRecap = new QVBoxLayout;
        labelRecap = new QLabel;

        labelRecap->setText(QString("Starting frequency (Hz): ")+ QString::number(freqStart)+"\n"
                            +"Stopping frequency (Hz): "+QString::number(freqStop)+"\n"
                            +"Sweep time (second): "+QString::number(sweepTime)+"\n"
                            +"Samples per sweep: "+QString::number(NTS)+"\n"
                            +"Wrote " +QString::number(write_count)+ " uint16 samples to a file.");

        layoutRecap->addWidget(labelRecap);

        fenetreRecap->setLayout(layoutRecap);
        fenetreRecap->setWindowTitle("Request data done");
        fenetreRecap->show();
        requestData_done = true;
    }
    else
    {
        QMessageBox::information(this, "Request Data", "You must first initialize the Radar and Update its parameter and Update the bandwith parameter");
    }
}

//bool is_greather_than(int i){return i >49152; }

void MaFenetre::processData()
{
    //    if(init_done &&  updateRadar_done && updateBandwith_done && requestData_done)
    //    {
    QString fichier = QFileDialog::getOpenFileName(this,"Ouvrir un fichier",QString());//Permet d'extraire le nom + chemin du fichier
    QByteArray nomFichier = fichier.toLocal8Bit();
    const char *addr_nomFichier = nomFichier.data();

    //Open the file
    //        FILE *file = std::fopen (addr_nomFichier, "rb");//addr_nomFichier ou "./sdr_kit_980AD2_data.bin"

    //        fseek(file,0,SEEK_END);
    //        int res = ftell(file);
    //        std::cout << res << std::endl;

    // Close our file handle
    //        std::fclose (file);

    std::ifstream file(addr_nomFichier, std::ios::binary | std::ios::ate);//Ouverture du file en mode binaire avec le curseur déjà à la fin du document
    std:: streamsize size = file.tellg();//Retourne la position du curseur
    file.seekg(0,std::ios::beg);//Place le curseur au début

    std::vector<uint16_t> buffer(size/2);//Creation d'un buffer pour acceuillir le contenu du file
    //on divise size par 2 car il y a 2 char pour un short (or uint16_t est équivalent à un short) et size est la taille du fichier en char (octet)
    if(file.read((char *)buffer.data(),size))//On doit forcément caster le pointeur car la méthode read ne prend qu'un pointeur de char
    {
        std::cout << "Succefully copied" << std::endl;
        //            for(int i=0; i<6;i++)
        //            {
        //                std::cout << buffer[i] << std::endl;
        //            }
        //            std::cout << buffer.size() << std::endl;
        //            std::cout << buffer[buffer.size()-1] << std::endl;
        //Modulation scheme
        int MD = buffer[0];

        //Receiving Channel number
        int CH = buffer[1];

        //Starting Frenquency
        uint64_t Freq_start = buffer[2]*1e6;

        //Stopping Frequency
        uint64_t Freq_stop = buffer[3]*1e6;

        //SweepTime in second
        double SweepTime_extract = buffer[4]/1e6;

        double Tsweep = SweepTime_extract;

        //NTS: Sample per sweep
        int NTS_extract = buffer[5];

        std::vector<uint16_t> rawData((size/2)-6);// même explication qu'en dessous
        std::copy (buffer.begin()+6,buffer.end(),rawData.begin());//le + 6 car les 6 premières valeur ne corresponde
        //pas à des données  mes des paramètre de l'enregistrement

        fenetreExtract = new QDialog;
        layoutExtract = new QVBoxLayout;
        labelExtract = new QLabel;

        labelExtract->setText(QString("Number of Receiving channel: ")+ QString::number(CH)+"\n"
                              +"Starting frequency (Hz): "+ QString::number(Freq_start)+"\n"
                              +"Stopping frequency (Hz): "+QString::number(Freq_stop)+"\n"
                              +"Sweep time (second): "+QString::number(SweepTime_extract)+"\n"
                              +"Samples per sweep: "+QString::number(NTS_extract));

        layoutExtract->addWidget(labelExtract);

        fenetreExtract->setLayout(layoutExtract);
        fenetreExtract->setWindowTitle("Recap extracted Data");
        fenetreExtract->show();
        file.close();
        double Np =0;
        switch (CH) {
        case 2:
        {
            Np = floor(rawData.size()/2.0/2.0/(double)NTS_extract);
            double dT=SweepTime_extract;
            double T = dT*Np;
            double F = 1/dT;
            double prf = 1/dT;

            int Samp_rate = 1/SweepTime_extract*NTS_extract;
            int Dopp_fezq = 1/SweepTime_extract;
            int Bandwidth = Freq_stop-Freq_start;

            int Bw = Bandwidth;
            //Permet de trouver le premier indice de i1
            std::vector<uint16_t>::iterator index = std::find_if(rawData.begin(),rawData.end(),[](int i){return i >49152;});
            int index_utilisable = index - rawData.begin();
            //                std::cout << index_utilisable << std::endl;


            //Les boucles while permettent d'extraire les tableau I1 Q1 I2 Q2 de rawData
            int index_i1 =index_utilisable;
            std::vector<uint16_t> I1;

            while(index_i1<Np*NTS_extract*4-3)
            {
                I1.push_back(rawData[index_i1]);
                index_i1+=4;
            }

            int index_q1 =index_utilisable+1;
            std::vector<uint16_t> Q1;

            while(index_q1<Np*NTS_extract*4-2)
            {
                Q1.push_back(rawData[index_q1]);
                index_q1+=4;
            }

            int index_i2 =index_utilisable+2;
            std::vector<uint16_t> I2;

            while(index_i2<Np*NTS_extract*4-1)
            {
                I2.push_back(rawData[index_i2]);
                index_i2+=4;
            }

            int index_q2 =index_utilisable+3;
            std::vector<uint16_t> Q2;

            while(index_q2<Np*NTS_extract*4)
            {
                Q2.push_back(rawData[index_q2]);
                index_q2+=4;
            }

            //                std::cout << I1[0] << std::endl;
            //                std::cout << I1[I1.size()-1] << std::endl;
            //                std::cout << I1.size() << std::endl;

            //                std::cout << Q1[0] << std::endl;
            //                std::cout << Q1[Q1.size()-1] << std::endl;
            //                std::cout << Q1.size() << std::endl;

            //                std::cout << I2[0] << std::endl;
            //                std::cout << I2[I2.size()-1] << std::endl;
            //                std::cout << I2.size() << std::endl;

            //                std::cout << Q2[0] << std::endl;
            //                std::cout << Q2[Q2.size()-1] << std::endl;
            //                std::cout << Q2.size() << std::endl;

            std::vector<int> header_index;

            for(int i=0; i<I1.size(); i++)
            {
                if(I1[i]>= 49152)
                {
                    header_index.push_back(i);
                }
            }
            //                std::cout << header_index[0] << std::endl;
            //                std::cout << header_index[header_index.size()-1] << std::endl;
            //                std::cout << header_index.size() << std::endl;

            // à faire la structure conditionnel (if) pour savoir si il y a eu des data loss

            for(int i=0; i<header_index.size(); i++)
            {
                I1[header_index[i]]=I1[header_index[i]]-49152;
            }

            long double mean_I1 = std::accumulate(I1.begin(),I1.end(),0.0);
            mean_I1 /= (double) I1.size();
            std::vector<double> I1_d;

            for(int i=0; i<I1.size(); i++)
            {
                I1_d.push_back(I1[i]-mean_I1);
            }

            long double mean_Q1 = std::accumulate(Q1.begin(),Q1.end(),0.0);
            mean_Q1 /= (double) Q1.size();
            std::vector<double> Q1_d;

            for(int i=0; i<Q1.size(); i++)
            {
                Q1_d.push_back(Q1[i]-mean_Q1);
            }

            long double mean_I2 = std::accumulate(I2.begin(),I2.end(),0.0);
            mean_I2 /= (double) I2.size();
            std::vector<double> I2_d;

            for(int i=0; i<I2.size(); i++)
            {
                I2_d.push_back(I2[i]-mean_I2);
            }

            long double mean_Q2 = std::accumulate(Q2.begin(),Q2.end(),0.0);
            mean_Q2 /= (double) Q2.size();
            std::vector<double> Q2_d;

            for(int i=0; i<Q2.size(); i++)
            {
                Q2_d.push_back(Q2[i]-mean_Q2);
            }

//            std::cout << I1_d[0] << std::endl;
//            std::cout << I1_d[I1_d.size()-1] << std::endl;
//            std::cout << I1_d.size() << std::endl;

//            std::cout << Q1_d[0] << std::endl;
//            std::cout << Q1_d[Q1_d.size()-1] << std::endl;
//            std::cout << Q1_d.size() << std::endl;

//            std::cout << I2_d[0] << std::endl;
//            std::cout << I2_d[I2_d.size()-1] << std::endl;
//            std::cout << I2_d.size() << std::endl;

//            std::cout << Q2_d[0] << std::endl;
//            std::cout << Q2_d[Q2_d.size()-1] << std::endl;
//            std::cout << Q2_d.size() << std::endl;

            QVector<double> time;
            time = linspace(0.0,T,(double)I1.size());
            QVector<double> I1_Q = QVector<double>::fromStdVector(I1_d);
            QVector<double> Q1_Q = QVector<double>::fromStdVector(Q1_d);

            graph_1 = new graph;
            graph_1->setWindowTitle("Graphique I1 & Q1");
            graph_1->makePlot_I_Q(I1_Q,Q1_Q,time);
            graph_1->show();

            QVector<double> I2_Q = QVector<double>::fromStdVector(I2_d);
            QVector<double> Q2_Q = QVector<double>::fromStdVector(Q2_d);

            graph_2 = new graph;
            graph_2->setWindowTitle("Graphique I2 & Q2");
            graph_2->makePlot_I_Q(I2_Q,Q2_Q,time);
            graph_2->show();

            //Transformation Data pour traitement FFT

            //Define the length of the complex array

            int N = I1_Q.size();

            double fs = NTS_extract/Tsweep;
            double record_length = (double)N/NTS_extract*Tsweep;
            int nc = floor(record_length/Tsweep);

            //Input array

            fftw_complex *Data1,*Data2,*Data,*out;
            fftw_plan plan;

            Data1 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N);
            Data2 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N);
            Data = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*NTS_extract);
            out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*NTS_extract);

            plan = fftw_plan_dft_1d(NTS_extract,Data,out, FFTW_FORWARD,FFTW_ESTIMATE);


            for(int i=0;i<N;i++)
            {
                Data1[i][REAL]=I1_Q[i];
                Data1[i][IMAG]=Q1_Q[i];

                Data2[i][REAL]=I2_Q[i];
                Data2[i][IMAG]=Q2_Q[i];
            }

            //Data needed for the following
            std::vector<double> real_out (NTS_extract);
            std::vector<double> imag_out(NTS_extract);

            std::vector<std::vector<double>> real_fft_shifted (nc,std::vector<double>(NTS_extract));


            for(int i=0; i<nc*NTS_extract; i+=128 )
            {
                for(int j=0;j<NTS_extract;j++)
                {
                    Data[j][REAL]=Data2[i+j][REAL];
                    Data[j][IMAG]=Data2[i+j][IMAG];
                }

                fftw_execute(plan);

                for(int k=0; k<NTS_extract;k++)
                {
                    real_out[k]=out[k][REAL];
                    imag_out[k]=out[k][IMAG];
                }

                fftwShift(real_out);
                fftwShift(imag_out);


            }

            for(int i =0; i<NTS_extract;i++)
            {
                std::cout << real_out[i] << " + i "<< imag_out[i] <<std::endl;
            }

            fftw_destroy_plan(plan);
            fftw_free(Data1);
            fftw_free(Data2);
            fftw_free(Data);
            fftw_free(out);

            std::cout << "Stop" << std::endl;
            std::cout << real_fft_shifted.size() << std::endl;
            std::cout << real_fft_shifted[0].size() << std::endl;

        }
            break;
        default:
            std::cout << "Erreur nombre de receiving channel non reconnu" << std::endl;
            break;
        }

    }


    //    }
    //    else
    //    {
    //        QMessageBox::information(this, "Process Data", "You must first initialize the Radar and Update its parameter and Update the bandwith parameter and Request Data");
    //    }
}


QVector<double> MaFenetre::linspace(double start, double end, double num)
{
    QVector<double> linspaced;

    if (0 != num)
    {
        if (1 == num)
        {
            linspaced.push_back(static_cast<double>(start));
        }
        else
        {
            double delta = (end - start) / (num - 1);

            for (auto i = 0; i < (num - 1); ++i)
            {
                linspaced.push_back(static_cast<double>(start + delta * i));
            }
            // ensure that start and end are exactly the same as the input
            linspaced.push_back(static_cast<double>(end));
        }
    }
    return linspaced;
}

void MaFenetre::fftwShift(std::vector<double>&data_shift)
{
    int N_shift = data_shift.size();
    //even number of element
    if(N_shift%2==0)
        std::rotate(&data_shift[0],&data_shift[N_shift >> 1], &data_shift[N_shift]);
    //odd number
    else
        std::rotate(&data_shift[0],&data_shift[(N_shift >> 1)+1], &data_shift[N_shift]);

}
