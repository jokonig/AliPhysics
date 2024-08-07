/// @brief run mode: 1 EMCal ;2 PCM;3 PHOS;4 PCMEMCal;5 PCMPHOS;
/// @param period
/// @param runMode
/// @param trainConfig
void AddTaskGammaV2(
    TString period = "",
    Int_t runMode = 0,
    TString trainConfig = "0" // additional counter for trainconfig
)
{

    AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
    if (!mgr)
    {
        return;
    }
    AliVEventHandler *inputHandler = mgr->GetInputEventHandler();
    AliAnalysisDataContainer *cinput = mgr->GetCommonInputContainer();
    TList *EventCutList = new TList();
    EventCutList->SetOwner(kTRUE);
    Int_t nCuts = 4;
    if (runMode == 1 || runMode == 3)
    {
        AliAnalysisTaskGammaCaloV2 *fGammaCalo = nullptr;
        fGammaCalo = (AliAnalysisTaskGammaCaloV2 *)mgr->GetTask(Form("GammaCalo_%i", trainConfig.Atoi()));
        if (!fGammaCalo)
        {
            cout << "===============GammaCalo not found!!!!===================" << endl;
            return;
        }
        nCuts = fGammaCalo->GetCutsNumber();
        EventCutList = fGammaCalo->GetEventCutList();
    }
    if (runMode == 2)
    {
        AliAnalysisTaskGammaConvFlowV1 *fGammaCaloV1 = nullptr;
        fGammaCaloV1 = (AliAnalysisTaskGammaConvFlowV1 *)mgr->GetTask(Form("GammaConvV1_%i", trainConfig.Atoi()));
        if (!fGammaCaloV1)
        {
            cout << "===============GammaCaloV1 not found!!!!===================" << endl;
            return;
        }
        nCuts = fGammaCaloV1->GetCutsNumber();
        EventCutList = fGammaCaloV1->GetEventCutList();
    }

    // now  create an instance of task
    AliAnalysisTaskPi0EtaV2 *task = new AliAnalysisTaskPi0EtaV2(Form("FlowTask_%i", trainConfig.Atoi())); //
    if (!task)
    {
        return;
    }
    task->SetnCuts(nCuts);
    // tsak->SetRunMode(runMode);
    //  task->SetCent(cent);
    task->SetPeriod(period);
    task->SetCutList(EventCutList);
    task->SetTrainconfig(trainConfig.Atoi());
    mgr->AddTask(task);

    //  mgr->ConnectInput(task,0,mgr->GetCommonInputContainer());
    // same for the output

    AliAnalysisDataContainer *coutput_result = mgr->CreateContainer(Form("Flow_runMode%i", runMode), TList::Class(),
                                                                    AliAnalysisManager::kOutputContainer,
                                                                    "AnalysisResults.root");
    mgr->ConnectInput(task, 0, cinput);
    mgr->ConnectOutput(task, 1, coutput_result);

    //  mgr->ConnectOutput(task,1,mgr->CreateContainer("MyOutputContainer", TList::Class(), AliAnalysisManager::kOutputContainer, fileName.Data()));
    // in the end, this macro returns a pointer to your task. this will be convenient later on
    // when you will run your analysis in an analysis train on grid
    return;
} /// 111
