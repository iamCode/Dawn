#ifndef CONFIGURABLEFRAME_H
#define CONFIGURABLEFRAME_H

#include "FramesBase.h"
#include "ControlElement.h"

class ConfigurableFrame : public FramesBase //, public ControlElement
{
	public:
		ConfigurableFrame( int contentX, int contentY, int contentWidth, int contentHeight );
		virtual void draw( int mouseX, int mouseY );
		virtual void clicked( int mouseX, int mouseY, uint8_t mouseState );

		void setAutoresize();
		void setCenteringLayout();
		void setCenterOnScreen();

		virtual void addChildFrame( int relPosX, int relPosY, std::auto_ptr<FramesBase> newChild );
		virtual int getWidth() const;
		virtual int getHeight() const;

	private:
		void applyLayout();
		void resize( int width, int height );
		void recalculatePosition();

		int contentX;
		int contentY;
		int blocksX;
		int blocksY;

		bool autoResize;
		bool centeringLayout;
		bool centerOnScreen;
};

#endif // CONFIGURABLEFRAME_H
