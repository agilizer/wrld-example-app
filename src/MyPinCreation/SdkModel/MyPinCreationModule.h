// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPinCreation.h"
#include "IMyPinCreationModule.h"
#include "Modules.h"
#include "VectorMathDecl.h"
#include "Camera.h"
#include "Rendering.h"
#include "Terrain.h"
#include "IIdentity.h"
#include "Menu.h"
#include "Search.h"
#include "IdTypes.h"
#include "MyPins.h"
#include "MyPinCreationModelObserver.h"
#include "MyPinCreationViewStateChangedHandler.h"
#include "MyPinCreationViewSavePinHandler.h"
#include "BidirectionalBus.h"
#include "IReactionControllerModel.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace SdkModel
        {
            class MyPinCreationModule : public IMyPinCreationModule
            {
            public:
                MyPinCreationModule(MyPins::SdkModel::IMyPinsService& myPinsService,
                                    Eegeo::Helpers::IIdentityProvider& identityProvider,
                                    ExampleApp::Menu::View::IMenuViewModel& menuViewModel,
                                    Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                    Search::SdkModel::ISearchRefreshService& searchRefreshService,
                                    ScreenControl::View::IScreenControlViewModel& interiorControlViewModel,
                                    ExampleAppMessaging::TMessageBus& messageBus,
                                    Reaction::View::IReactionControllerModel& reactionControllerModel);

                ~MyPinCreationModule();

                IMyPinCreationModel& GetMyPinCreationModel() const;
                View::IMyPinCreationConfirmationViewModel& GetMyPinCreationConfirmationViewModel() const;
                View::IMyPinCreationCompositeViewModel& GetMyPinCreationCompositeViewModel() const;

                //ScreenControl::View::IScreenControlViewModel& GetInitiationScreenControlViewModel() const;
                ScreenControl::View::IScreenControlViewModel& GetConfirmationScreenControlViewModel() const;

                OpenableControl::View::IOpenableControlViewModel& GetObservableOpenableControl() const;
                
                Menu::View::IMenuModel& GetMyPinCreationMenuModel() const
                {
                    return *m_pMyPinCreationMenuModel;
                }
                
            private:

                MyPinCreationModel* m_pMyPinCreationModel;
               
                View::MyPinCreationConfirmationViewModel* m_pMyPinCreationConfirmationViewModel;
                View::MyPinCreationCompositeViewModel* m_pMyPinCreationCompositeViewModel;
                MyPinCreationModelObserver* m_pMyPinCreationModelObserver;
                MyPinCreationViewStateChangedHandler* m_pMyPinCreationViewStateChangedHandler;
                MyPinCreationViewSavePinHandler* m_pMyPinCreationViewSavePinHandler;
                
                
                Menu::View::IMenuModel* m_pMyPinCreationMenuModel;
                Menu::View::IMenuOptionsModel* m_pMyPinCreationMenuOptionsModel;
            };
        }
    }
}
