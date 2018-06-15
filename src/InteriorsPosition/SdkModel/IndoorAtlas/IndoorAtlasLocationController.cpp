// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "IndoorAtlasLocationController.h"
#include "InteriorSelectionModel.h"
#include "InteriorInteractionModel.h"
#include "IPSConfigurationParser.h"
#include "AboutPageIndoorPositionSettingsMessage.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace IndoorAtlas
            {
                IndoorAtlasLocationController::IndoorAtlasLocationController(IndoorAtlasLocationService& locationService,
                                                                            ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                                                            const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                            Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository)
                : m_locationService(locationService)
                , m_appModeModel(appModeModel)
                , m_interiorSelectionModel(interiorSelectionModel)
                , m_appModeChangedCallback(this, &IndoorAtlasLocationController::OnAppModeChanged)
                , m_interiorMetaDataRepository(interiorMetaDataRepository)
                {
                    m_appModeModel.RegisterAppModeChangedCallback(m_appModeChangedCallback);
                }
                
                IndoorAtlasLocationController::~IndoorAtlasLocationController()
                {
                    m_appModeModel.UnregisterAppModeChangedCallback(m_appModeChangedCallback);
                }
                
                void IndoorAtlasLocationController::OnAppModeChanged()
                {
                    // todo loc: duplicate code in service
                    m_locationService.StopUpdating();
                    
                    if(m_appModeModel.GetAppMode() != AppModes::SdkModel::InteriorMode)
                    {
                        return;
                    }
                    
                    const auto interiorId = m_interiorSelectionModel.GetSelectedInteriorId();
                    
                    if(!interiorId.IsValid())
                    {
                        return;
                    }
                    
                    typedef std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo> TrackingInfoMap;
                    TrackingInfoMap trackingInfoMap;
                    InteriorsPosition::TryAndGetInteriorTrackingInfo(trackingInfoMap, interiorId, m_interiorMetaDataRepository);
                    
                    const TrackingInfoMap::const_iterator trackingInfoEntry = trackingInfoMap.find(interiorId.Value());
                    
                    if (trackingInfoEntry == trackingInfoMap.end())
                    {
                        return;
                    }
                    
                    const auto& trackingInfo = trackingInfoEntry->second;
                    
                    if (trackingInfo.GetType() != "IndoorAtlas")
                    {
                        return;
                    }
                    
                    m_locationService.StartUpdating();
                }
            }
        }
    }
}
