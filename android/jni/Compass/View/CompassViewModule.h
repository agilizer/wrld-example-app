// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICompassViewModule.h"
#include "AndroidNativeState.h"
#include "Types.h"
#include "Compass.h"
#include "CompassViewIncludes.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View
        {
            class CompassViewModule: public ICompassViewModule, private Eegeo::NonCopyable
            {
            private:
                CompassView* m_pView;
                CompassController* m_pController;

            public:
                CompassViewModule(
                    AndroidNativeState& nativeState,
                    ICompassViewModel& viewModel,
                    ExampleAppMessaging::TMessageBus& messageBus
                );

                ~CompassViewModule();

                ICompassView& GetCompassView();
            };
        }
    }
}
