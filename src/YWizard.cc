/*---------------------------------------------------------------------\
|								       |
|		       __   __	  ____ _____ ____		       |
|		       \ \ / /_ _/ ___|_   _|___ \		       |
|			\ V / _` \___ \ | |   __) |		       |
|			 | | (_| |___) || |  / __/		       |
|			 |_|\__,_|____/ |_| |_____|		       |
|								       |
|				core system			       |
|							 (C) SuSE GmbH |
\----------------------------------------------------------------------/

  File:		YWizard.cc

  Author:	Stefan Hundhammer <sh@suse.de>

/-*/


#define YUILogComponent "ui"
#include "YUILog.h"

#include "YWizard.h"
#include "YPushButton.h"
#include "YReplacePoint.h"


struct YWizardPrivate
{
    YWizardPrivate( YWizardMode wizardMode )
	: wizardMode( wizardMode )
	, nextButtonIsProtected( false )
	, idsDisabledCount( 0 )
	{}

    YWizardMode	wizardMode;
    bool	nextButtonIsProtected;
    int		idsDisabledCount;
};




YWizard::YWizard( YWidget *		parent,
		  const string & 	backButtonLabel,
		  const string & 	abortButtonLabel,
		  const string & 	nextButtonLabel,
		  YWizardMode 		wizardMode )
    : YWidget( parent )
    , priv( new YWizardPrivate( wizardMode ) )
{
    YUI_CHECK_NEW( priv );

    // On the YWidget level, a Wizard has a content area and a couple of
    // buttons as children, so simply subclassing from YSimpleChildManager
    // won't do; a children manager that can handle more children is needed.
    setChildrenManager( new YWidgetChildrenManager( this ) );

    setDefaultStretchable( YD_HORIZ, true );
    setDefaultStretchable( YD_VERT,  true );
}


YWizard::~YWizard()
{
    YWizard * parentWizard = wizardParent();

    if ( parentWizard )
	parentWizard->setInternalIdsEnabled( true );
}


YWizardMode
YWizard::wizardMode() const
{
    return priv->wizardMode;
}


YWizard *
YWizard::wizardParent() const
{
    YWidget * widget = parent();

    while ( widget )
    {
	YWizard * wizard = dynamic_cast<YWizard *> (widget);

	if ( wizard )
	    return wizard;

	widget = widget->parent();
    }

    return 0;
}


bool
YWizard::nextButtonIsProtected() const
{
    return priv->nextButtonIsProtected;
}


void
YWizard::protectNextButton( bool protect )
{
    priv->nextButtonIsProtected = protect;
}


void
YWizard::setButtonLabel( YPushButton * button, const string & label )
{
    // FIXME: Throw exception? ( YUI_CHECK_PTR() )
    
    if ( button )
	button->setLabel( label );
    else
	yuiError() << "NULL button" << endl;
}


void
YWizard::ping()
{
    yuiDebug() << "YWizard is active" << endl;
}


void
YWizard::setInternalIdsEnabled( bool enabled )
{
    if ( enabled )
	priv->idsDisabledCount--;
    else
    	priv->idsDisabledCount++;

    if ( enabled && priv->idsDisabledCount > 0 )
	return;

    this->setIdEnabled( enabled );
    
    if ( backButton()  )	backButton ()->setIdEnabled( enabled );
    if ( abortButton() )	abortButton()->setIdEnabled( enabled );
    if ( nextButton()  )	nextButton ()->setIdEnabled( enabled );

    if ( contentsReplacePoint() ) contentsReplacePoint()->setIdEnabled( enabled );
}


const YPropertySet &
YWizard::propertySet()
{
    static YPropertySet propSet;

    if ( propSet.isEmpty() )
    {
	/*
	 * @property string CurrentItem	the currently selected tree item (read only)
	 */
	propSet.add( YProperty( YUIProperty_CurrentItem, YStringProperty, true ) );	// read-only
	propSet.add( YWidget::propertySet() );
    }

    return propSet;
}


YPropertyValue
YWizard::getProperty( const string & propertyName )
{
    propertySet().check( propertyName ); // throws exceptions if not found

    if ( propertyName == YUIProperty_CurrentItem )	return YPropertyValue( YOtherProperty );
    else
    {
	return YWidget::getProperty( propertyName );
    }
}