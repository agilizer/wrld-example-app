// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingModule.h"
#include "NavRoutingModel.h"
#include "NavRoutingPolylineFactory.h"
#include "NavRouteDrawingController.h"
#include "NavRoutingServiceController.h"
#include "NavWidgetRouteUpdateHandler.h"
#include "NavWidgetRouteDrawingHandler.h"
#include "NavRoutingController.h"
#include "RouteService.h"
#include "NavTurnByTurnModel.h"
#include "NavTurnByTurnController.h"
#include "NavRoutingCameraController.h"
#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "NavWidgetMenuOption.h"
#include "NavTurnByTurnCompletionHandler.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            NavRoutingModule::NavRoutingModule(PolyLineArgs::IShapeService& shapeService,
                                                Eegeo::Routes::Webservice::IRoutingWebservice& routingWebservice,
                                                Eegeo::Location::ILocationService& locationService,
                                                Eegeo::Location::NavigationService& navigationService,
                                                Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                                                CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                Compass::SdkModel::ICompassModel& compassModel,
                                                ExampleAppMessaging::TMessageBus& messageBus,
                                                Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                                                Eegeo::Markers::IMarkerService& markerService,
                                                WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                               GpsMarker::SdkModel::GpsMarkerModel& gpsMarkerModel,
                                               WorldPins::SdkModel::IWorldPinsVisibilityController& worldPinsVisibilityController)
            {
                const std::string navUIOptionText = "Open Navigation";
                m_pNavRoutingModel = Eegeo_NEW(NavRoutingModel)();
                
                NavRoutingPolylineConfig polylineConfig = NavRoutingPolylineConfig();
                m_pNavRoutingPolylineFactory = Eegeo_NEW(NavRoutingPolylineFactory)(shapeService,
                                                                                    polylineConfig);
                
                m_pNavRouteDrawingController = Eegeo_NEW(NavRouteDrawingController)(*m_pNavRoutingModel,
                                                                                    *m_pNavRoutingPolylineFactory,
                                                                                    shapeService,
                                                                                    markerService);
                
                m_pNavRoutingServiceController = Eegeo_NEW(NavRoutingServiceController)(routingWebservice);

                m_pRouteUpdateHandler = Eegeo_NEW(NavWidgetRouteUpdateHandler)(*m_pNavRoutingModel,
                                                                               *m_pNavRoutingServiceController,
                                                                               interiorsModelRepository,
                                                                               alertBoxFactory,
                                                                               messageBus);

                TurnByTurn::NavTurnByTurnConfig turnByTurnConfig = TurnByTurn::NavTurnByTurnConfig();

                m_pTurnByTurnModel = Eegeo_NEW(TurnByTurn::NavTurnByTurnModel)(turnByTurnConfig,
                                                                               locationService,
                                                                               interiorsModelRepository);

                m_pTurnByTurnController = Eegeo_NEW(TurnByTurn::NavTurnByTurnController)(*m_pTurnByTurnModel,
                                                                                         *m_pNavRoutingModel,
                                                                                         navigationService,
                                                                                         gpsMarkerModel);
                
                m_pTurnByTurnCompletionHandler = Eegeo_NEW(TurnByTurn::NavTurnByTurnCompletionHandler)(*m_pTurnByTurnModel,
                                                                                                       *m_pNavRoutingModel,
                                                                                                       locationService,
                                                                                                       turnByTurnConfig.accuracyMultiplierToCompleteNavigation,
                                                                                                       turnByTurnConfig.minDistanceToCompleteNavigation);
                
                m_pRouteDrawingHandler = Eegeo_NEW(NavWidgetRouteDrawingHandler)(*m_pNavRoutingModel,
                                                                                 *m_pTurnByTurnModel,
                                                                                 *m_pNavRouteDrawingController);

                m_pNavRoutingLocationFinder = Eegeo_NEW(NavRoutingLocationFinder)(locationService,
                                                                                  interiorsModelRepository,
                                                                                  alertBoxFactory);

                m_pRoutingController = Eegeo_NEW(NavRoutingController)(*m_pNavRoutingModel,
                                                                       *m_pTurnByTurnModel,
                                                                       *m_pNavRoutingLocationFinder,
                                                                       messageBus,
                                                                       worldPinsService);

                
                m_pRoutingCameraController = Eegeo_NEW(NavRoutingCameraController)(*m_pNavRoutingModel,
                                                                                   cameraTransitionController,
                                                                                   navigationService,
                                                                                   compassModel);
                
                m_pRoutingWorldPinsVisibilityHandler = Eegeo_NEW(NavRoutingWorldPinsVisibilityHandler)(messageBus,
                                                                                                       worldPinsVisibilityController);
                
                m_pMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                m_pMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pMenuModel);
                m_pMenuOptionsModel->AddItem(navUIOptionText,
                                             navUIOptionText, "", "",
                                           Eegeo_NEW(View::NavWidgetMenuOption)(
                                                   *m_pNavRoutingLocationFinder,
                                                   *m_pNavRoutingModel,
                                                   *m_pRoutingController));
            }

            NavRoutingModule::~NavRoutingModule()
            {
                Eegeo_DELETE m_pRoutingWorldPinsVisibilityHandler;
                Eegeo_DELETE m_pRoutingCameraController;
                Eegeo_DELETE m_pRoutingController;
                Eegeo_DELETE m_pRouteDrawingHandler;
                Eegeo_DELETE m_pTurnByTurnCompletionHandler;
                Eegeo_DELETE m_pTurnByTurnController;
                Eegeo_DELETE m_pNavRoutingLocationFinder;
                Eegeo_DELETE m_pTurnByTurnModel;
                Eegeo_DELETE m_pRouteUpdateHandler;
                Eegeo_DELETE m_pNavRoutingServiceController;
                Eegeo_DELETE m_pNavRouteDrawingController;
                Eegeo_DELETE m_pNavRoutingPolylineFactory;
                Eegeo_DELETE m_pNavRoutingModel;
                Eegeo_DELETE m_pMenuOptionsModel;
                Eegeo_DELETE m_pMenuModel;
            }

            void NavRoutingModule::Update(float dt)
            {
                m_pTurnByTurnController->Update(dt);
            }

            INavRouteDrawingController& NavRoutingModule::GetRouteDrawingController()
            {
                return *m_pNavRouteDrawingController;
            }

            INavRoutingServiceController& NavRoutingModule::GetRoutingServiceController()
            {
                return *m_pNavRoutingServiceController;
            }

            Menu::View::IMenuModel& NavRoutingModule::GetNavMenuModel() const
            {
                return *m_pMenuModel;
            }
        }
    }
}
