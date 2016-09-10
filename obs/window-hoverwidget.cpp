
#include "window-hoverwidget.hpp"
#include "obs-app.hpp"
#include "qt-wrappers.hpp"
#include "tblive_sdk/tblive_sdk.h"
#include <windows.h>
namespace {

bool IsChildWidget(QWidget * child, QWidget * parent)
{
	QWidget * childParent = child;
	while ( childParent )
	{
		if ( childParent == parent )
		{
			return true;
		}
		else
		{
			childParent = childParent->parentWidget();
		}
	}

	return false;
}

}// namespace

VolHoverWidget::VolHoverWidget(QWidget *parent)
	: QDockWidget(parent, Qt::FramelessWindowHint),
	  ui(new Ui::HoverWidget)
{
	ui->setupUi(this);

	QWidget * emptyTitle = new QWidget(this);
	setTitleBarWidget(emptyTitle);

	// focus
	setFocusPolicy(Qt::StrongFocus);

	SetWindowPos((HWND)winId(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	ImplInstallEventFilter();
}

void VolHoverWidget::ImplInstallEventFilter()
{
	ui->scrollArea->installEventFilter(this);
	ui->volumeWidgets->installEventFilter(this);
}

bool VolHoverWidget::eventFilter(QObject *target, QEvent *event)
{
	//����ͣ�ã���Ϊ����Ĵ���  
	if (QEvent::WindowDeactivate == event->type())
	{
		hide();
		return true;
	}

	return false;
}

void VolHoverWidget::RecheckInputOutputAudioSrc()
{
	//ö���豸
	//tblive_sdk::check_add_all_audio_sources_to_current_scene();
}

void VolHoverWidget::ShowAt(int px, int py)
{
	show();
	//ˮƽ������pxΪ�е���ʾ
	move(px - width() / 2, py - height() -5);

	activateWindow();

}

void VolHoverWidget::AddWidget2Layout(QWidget *w)
{
	ui->volumeWidgets->layout()->addWidget(w);
	w->installEventFilter(this);
	QList<QWidget *> pWidgetList = w->findChildren<QWidget *>();
	for (int i = 0; i < pWidgetList.count(); i++)
	{ 
		pWidgetList.at(i)->installEventFilter(this);
	}
	
}

