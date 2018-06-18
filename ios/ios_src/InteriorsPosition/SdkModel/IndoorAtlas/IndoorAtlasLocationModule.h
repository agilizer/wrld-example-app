// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "IndoorAtlasIncludes.h"
#include "AppModes.h"
#include "InteriorsExplorer.h"
#include "ApplicationConfiguration.h"
#include "ILocationService.h"
#include "BidirectionalBus.h"
#include "Rendering.h"
#include "InteriorMetaDataRepository.h"

@class IndoorAtlasLocationManager;

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace IndoorAtlas
            {
                class IndoorAtlasLocationModule
                {
                public:
                    IndoorAtlasLocationModule(ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                              Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                              const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                              const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                              Eegeo::Location::ILocationService& defaultLocationService,
                                              Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository,
                                              ExampleAppMessaging::TMessageBus& messageBus);
                    ~IndoorAtlasLocationModule();
            
                    IndoorAtlasLocationService& GetLocationService() { return *m_pLocationService; }
            
                private:
                    IndoorAtlasLocationService* m_pLocationService;
                    IndoorAtlasLocationController* m_pLocationController;
                };
            }
        }
    }
}
