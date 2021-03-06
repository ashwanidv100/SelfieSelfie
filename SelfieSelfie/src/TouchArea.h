//
//  TouchArea.h
//
//  Created by Soso Limited on 6/10/15.
//
//

#pragma once

#include "cinder/Signals.h"
#include "cinder/app/TouchEvent.h"
#include "cinder/Rect.h"

namespace soso {

///
/// A rectangle that calls a function on tap.
/// No coordination between touch areas.
///
class TouchArea
{
public:
	~TouchArea()
	{
		disconnect();
	}

	static std::unique_ptr<TouchArea> create( const ci::Rectf &iBounds, const std::function<void ()> &iCallback, int iPriority = 10 );

	void setEnabled( bool iEnabled ) { enabled = iEnabled; }
	bool isEnabled() const { return enabled; }

	const ci::Rectf& getBounds() const { return bounds; }

private:
	ci::Rectf								bounds;
	std::function<void ()>	callback;
	uint32_t								trackedTouch = 0;
	bool										wasInside = false;
	bool										enabled = true;
	ci::signals::Connection	touchBeginConnection, touchEndConnection;

	void touchBegin( ci::app::TouchEvent &iEvent );
	void touchEnd( ci::app::TouchEvent &iEvent );
	void connect( int iPriority );
	void disconnect();

	TouchArea( const ci::Rectf &iBounds, const std::function<void ()> &iCallback, int iPriority )
	: bounds( iBounds ),
		callback( iCallback )
	{
		connect( iPriority );
	}
};

} // namespace soso
