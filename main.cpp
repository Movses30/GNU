#include <QtWidgets/QSpacerItem>
#include<QStringList>
#include<QTextStream>
#include<QJsonDocument>
#include<QFile>
#include"class.h"
#include <string>
#include <QtCore/QVariant>
#include<QJsonObject>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QCheckBox>
#include <QVBoxLayout>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include<QDialog>
#include <QDialogButtonBox>
#include <QtWidgets/QPushButton>
#include <QLabel>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <iostream>
#include <QJsonArray>

void myChecBox::mySlotChekBox(bool b) 

{ 
  if ( true == b)
	this ->setDisabled(true);
  else  
	this ->setDisabled(false);
  if (true == b)
	this ->setChecked(true);
  else
	this ->setChecked(false);
}




void CorAPB3Configurator::saveSlot()
{
  QFile file(("frst.json"));
  QJsonObject obj;

  obj.insert("APB Data Bus Width",  getDataBusWidthMemory().c_str());
  obj.insert("Nuber bits master",   getNuberBitsMasterMemory().c_str());
  obj.insert("position  upper 4 bits address", getPositionUpper4BitsMemory().c_str());
  obj.insert("Indicate Addressing", getIndirectAddresMemory().c_str());
  obj.insert("Allocate Memory",     getAllocateMemory()) ;
  obj.insert("Enable APB Memory",   getEenableAPBMemory()) ;
  obj.insert("Desable APB Memory",  getiDisableAPBMemory() );
  obj.insert("Testbench",           getTestBenchMemory().c_str());
  obj.insert("License",             getLicenseMemory().c_str());

  QJsonDocument Doc(obj);
  if(file.open(QIODevice::WriteOnly|QIODevice::Truncate))
  {
	file.write(Doc.toJson());
	file.close();
  }

}


std::string CorAPB3Configurator::getDataBusWidthMemory()
{
  if (m_pRButton32Bit->isChecked()  == true) 
	return m_pRButton32Bit->text().toStdString() ;

  if (m_pRButton16Bit->isChecked()  == true) 
	return m_pRButton16Bit->text().toStdString() ;

  if (m_pRButton8Bit->isChecked()  == true) 
	return m_pRButton8Bit->text().toStdString() ;

  return "error";
}

std::string CorAPB3Configurator::getNuberBitsMasterMemory()
{
  return m_pTexComboBoxNumber-> currentText().toStdString();
}

std::string CorAPB3Configurator::getPositionUpper4BitsMemory()
{
  return m_pTexComboBoxPosition-> currentText().toStdString();
}

std::string CorAPB3Configurator::getIndirectAddresMemory()
{
  return m_pTexComboBoxIndirect-> currentText().toStdString();
}

QJsonArray  CorAPB3Configurator::getAllocateMemory()
{
  QJsonArray arrAllocate;
  const int rowsGr2 =16; 
  for (int it =0;it < rowsGr2; ++ it)
  {
	if( (*mChBpArryAllocate)[it]-> isChecked() == true )
	  arrAllocate += QJsonValue(it);
  }
  return arrAllocate;
}

QJsonArray  CorAPB3Configurator::getEenableAPBMemory()
{
  QJsonArray arrEnable;
  const int rowsGr2 =16; 
  for (int i=0;i < rowsGr2; ++ i)
  {
	if( (*mChBpArryRnelARBwSlot)[i]-> isChecked() == true )
	{
	  arrEnable += QJsonValue(i);
	}
  }
  return arrEnable;
}

QJsonArray  CorAPB3Configurator::getiDisableAPBMemory()
{
  QJsonArray arrDisable;
  const int rowsGr2 =16; 
  for (int i=0;i < rowsGr2; ++ i)
  {
	if( (*mChBpArryRnelARBwSlot)[i]-> isEnabled() != true )
	{
	  arrDisable += QJsonValue(i);
	}
  }
  return arrDisable;
}

std::string CorAPB3Configurator::getTestBenchMemory()
{
  if (m_pComboBoxTestbench)
	return   m_pComboBoxTestbench-> currentText().toStdString();

  else
	return "error testBench";
}
std::string CorAPB3Configurator::getLicenseMemory()
{
  if (m_pRButtonObfuscat->isChecked()  == true) 
	return m_pRButtonObfuscat->text().toStdString();

  if (m_pRButtonRTL->isChecked()  == true) 
	return m_pRButtonRTL->text().toStdString();

  return "error";
}

QJsonObject  CorAPB3Configurator::JsonReadeAndSaved(QString in)
{
  QFile file(in);
  QJsonObject jsonObj;
  if( file.open( QIODevice::ReadOnly ) )
  {
	QByteArray bytes = file.readAll();
	file.close();

	QJsonDocument document = QJsonDocument::fromJson( bytes );
	jsonObj = document.object();
	for (  QJsonObject::const_iterator i = jsonObj.constBegin(); i != jsonObj.constEnd(); i++)
	{
	  QJsonArray arr = i.value().toArray();
	  if (i.key().toStdString() == "APB Data Bus Width")
	  {
		if(i.value().toString().toStdString() == "32-bit")
		  m_pRButton32Bit->setChecked(true);

		if(i.value().toString().toStdString() == "16-bit")
		  m_pRButton16Bit->setChecked(true);

		if(i.value().toString().toStdString() == "8-bit")
		  m_pRButton8Bit->setChecked(true);
	  }

	  else if(i.key().toStdString() == "Allocate Memory")
	  {
		for (QJsonArray::iterator j =arr.begin(); j != arr.end(); j++)
		{
		  ( *mChBpArryAllocate)[j->toInt()]->QAbstractButton::click();
		}
	  }

	  else if(i.key().toStdString() == "Desable APB Memory")
	  {
		for (QJsonArray::iterator j = arr.begin(); j != arr.end(); j++)
		{
		  ( *mChBpArryRnelARBwSlot)[j->toInt()]->QAbstractButton::click();
		}
	  }

	  else if(i.key().toStdString() == "Enable APB Memory")
	  {
		for (QJsonArray::iterator j = arr.begin(); j != arr.end(); j++)
		{
		  ( *mChBpArryRnelARBwSlot)[j->toInt()]->QAbstractButton::click();
		}
	  }

	  else if ( i.key().toStdString()=="Testbench")
	  {
		m_pComboBoxTestbench-> addItem(getNuberBitsMasterMemory().c_str()); 
	  }

	  if (i.key().toStdString() == "License")
	  {
		if(i.value().toString().toStdString() == "Obfuscate")
		{
		  m_pRButtonObfuscat->setChecked(true);
		}

		else if(i.value().toString().toStdString() == "RTL") 
		{
		  m_pRButtonRTL->setChecked(true);
		}
	  }

	  if ( i.key().toStdString()=="Nuber bits master")
	  {
		m_pTexComboBoxNumber->setCurrentText(i.value().toString());
	  }

	  if ( i.key().toStdString()=="position  upper 4 bits address")
	  {
		m_pTexComboBoxPosition->setCurrentText(i.value().toString());
	  }

	  if ( i.key().toStdString()=="indicateAddress")
	  {
		m_pTexComboBoxIndirect->setCurrentText(i.value().toString());
	  }

	  if ( i.key().toStdString()=="Testbench")
	  {
		m_pComboBoxTestbench->setCurrentText(i.value().toString());
	  }
	}
  }
  return jsonObj;
}

void CorAPB3Configurator::createTabConfigurator()
{
  m_pTabWidges              = new QTabWidget;
}

void CorAPB3Configurator::createTitlBaner()
{

    QLabel*        pLabelSmall    = new  QLabel();
    QLabel*        pLabelBig      = new  QLabel();
    QVBoxLayout *  pVLayoutBanner = new  QVBoxLayout();
    m_pTitleBanner                = new  QWidget();

    pLabelSmall->setText( "Actel:DirectCore:CoreAPB3:4.2.100" );
    QFont font = pLabelBig->font();
    font.setPointSize(20);
    pLabelBig->setFont(font);
    pLabelBig->setText( "CoreAPB3 Configurator" );
    pVLayoutBanner->addWidget( pLabelBig);
    pVLayoutBanner->addWidget ( pLabelSmall );

    m_pTitleBanner->setLayout ( pVLayoutBanner );
    m_pTitleBanner->setStyleSheet("* {color: qlineargradient(spread:pad, x1:0 y1:0,\
        x2:1 y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"\
	"background: qlineargradient( x1:1 y1:0, x2:0 y2:0, stop:0 cyan, stop:1 green);}");
}

void CorAPB3Configurator::createDataWidthConfiguration()
{
    m_pGetDataConfig = new QGroupBox("Data Widit Configuration");
    m_pGetDataConfig->setStyleSheet("QGroupBox {font: tbold; border: 1px solid silver;\
	  border-radius: 0px;margin-top: 6px;}QGroupBox::title {\
	  subcontrol-origin: margin;left: 7px;padding: 0px 0px 0px 0px; }");
    QLabel*     pLableDataConfig =  new QLabel("APB Master Data Bus Width");
    QHBoxLayout*    pHDataLayout = new QHBoxLayout;
    m_pRButton32Bit = new QRadioButton("32-bit");
    m_pRButton16Bit = new QRadioButton("16-bit");
    m_pRButton8Bit = new QRadioButton("8-bit");

    pHDataLayout->addWidget(pLableDataConfig);
    pHDataLayout->addWidget(m_pRButton32Bit);
    pHDataLayout->addWidget(m_pRButton16Bit);
    pHDataLayout->addWidget(m_pRButton8Bit);
    pHDataLayout->addItem(m_pHorizontalSpacer);
    m_pGetDataConfig->setLayout(pHDataLayout);
}

void CorAPB3Configurator::createAllocateMemryCheckBoxs()
{

      m_pGetAllocateMemory = new  QGroupBox("Allocate memory space to combined region slave");
      m_pGetAllocateMemory->setStyleSheet("QGroupBox {font: bold; border: 1px solid silver;\
	  border-radius: 0px;margin-top: 6px;}QGroupBox::title {\
	  subcontrol-origin: margin;left: 7px; padding: 0px 0px 0px 0px;}");

    QGridLayout* pGrLayoutAllocate = new QGridLayout();
    mChBpArryAllocate = new QVarLengthArray<QCheckBox*,16>(16);
    const int rowsGr2 =4, columnsGR2 =4;
    for (int i = 0; i < rowsGr2; ++ i)
      for (int j = 0; j < columnsGR2; ++j) {
    	pGrLayoutAllocate->setSpacing(15);
    	int iconNumbr =(i*columnsGR2+j);
    	std::string iconName = std::to_string(iconNumbr);
    	std::string iconName1 ="slot:" + iconName;
    	(*mChBpArryAllocate)[iconNumbr] = new myChecBox;
    	(*mChBpArryAllocate)[iconNumbr]->setText(iconName1.c_str());
    	(*mChBpArryAllocate)[iconNumbr]->setLayoutDirection(Qt::RightToLeft);

    	if( (i*4+j)>9)
    	  (*mChBpArryAllocate)[iconNumbr]->setStyleSheet("QCheckBox{ spacing:10px;}");

    	else
    	  (*mChBpArryAllocate)[iconNumbr]->setStyleSheet("QCheckBox{ spacing:18px;}");

    	pGrLayoutAllocate -> addWidget((*mChBpArryAllocate)[iconNumbr],i,j);
    	mChBpArryAllocate->append((*mChBpArryAllocate)[iconNumbr]);
      }

    pGrLayoutAllocate->setContentsMargins(10,22,10,10);
    pGrLayoutAllocate->addItem(m_pHorizontalSpacer,3,4);
    m_pGetAllocateMemory->setLayout(pGrLayoutAllocate);
}

void CorAPB3Configurator::createEnableAPBArrayCheckBoxs()
{  

    m_pGetEnablMemory   = new  QGroupBox("Enabled APB Slave Slots");
    m_pGetEnablMemory->setStyleSheet("QGroupBox {font: bold; border: 1px solid silver;\
	  border-radius: 0px;margin-top: 6px;}QGroupBox::title {\
	  subcontrol-origin: margin;left: 7px; padding: 0px 0px 0px 0px;}");

    QGridLayout* pGrLayoutEnabl = new QGridLayout();
    mChBpArryRnelARBwSlot = new QVarLengthArray<QCheckBox*,16>(16);
    const int rowsGr2 =4, columnsGR2 =4;
    for (int i = 0; i < rowsGr2; ++ i)
     {
      for (int j = 0; j < columnsGR2; ++j)
      {
    	pGrLayoutEnabl->setSpacing(15);
    	int iconNumbr =(i*columnsGR2+j);
    	std::string iconName = std::to_string(iconNumbr);
    	std::string iconName1 ="slot:" + iconName;
    	(*mChBpArryRnelARBwSlot)[iconNumbr] = new myChecBox;
    	(*mChBpArryRnelARBwSlot)[iconNumbr]->setText(iconName1.c_str());
    	(*mChBpArryRnelARBwSlot)[iconNumbr]->setLayoutDirection(Qt::RightToLeft);
    
    	if( (i*4+j)>9)
    	  (*mChBpArryRnelARBwSlot)[iconNumbr]->setStyleSheet("QCheckBox{ spacing:10px;}");

    	else
    	 (*mChBpArryRnelARBwSlot)[iconNumbr]->setStyleSheet("QCheckBox{ spacing:18px;}");

	    pGrLayoutEnabl -> addWidget((*mChBpArryRnelARBwSlot)[iconNumbr],i,j);
    	mChBpArryRnelARBwSlot->append((*mChBpArryRnelARBwSlot)[iconNumbr]);
      } 
    }
    pGrLayoutEnabl ->setContentsMargins(10,22,10,10);
    pGrLayoutEnabl ->addItem(m_pHorizontalSpacer,3,4);
    m_pGetEnablMemory->setLayout(pGrLayoutEnabl);
     
     for  (int i =0;i <15 ;i++)
     {
         for (int j = 0; j < 15 ; j++)
         {
         if (i == j)
             QObject::connect((*mChBpArryAllocate) [i], SIGNAL(toggled(bool)),  (*mChBpArryRnelARBwSlot)[j],SLOT(mySlotChekBox(bool)));
         }
     }

}

void CorAPB3Configurator::createTestbenchGrup()
{
      m_pTestBench        = new  QWidget();
      m_pLableTestB       = new  QLabel("Testbench:");
      createHorTestbenchLayout();
}

void CorAPB3Configurator::createHelpGrBox()
{
     m_pGetHelp = new QGroupBox();
     m_pGetHelp->setStyleSheet("QGroupBox {font: bold; border: 0px solid silver;\
	  border-radius: 0px;margin-top: 0px;}QGroupBox::title {\
	  subcontrol-origin: margin; left:0px; padding: 0px 0px 0px 0px;  }");
      createVerButtonlLayout(); 
}

void   CorAPB3Configurator::createAddressConfigFontComBox()
{
     QLabel*      	 pLableAddresNumber    = new QLabel();
     QLabel*      	 pLableAddrescPosition = new QLabel();
     QLabel*     	 pLableAddresIndirect  = new QLabel();
     m_pTexComboBoxNumber           = new  QComboBox;
     m_pTexComboBoxPosition         = new  QComboBox;
     m_pTexComboBoxIndirect         = new  QComboBox;

     QStringList list1=(QStringList()<<"24"<<"12"<<"6"<<"48");
     m_pTexComboBoxNumber->addItems(list1);
     QStringList list2=(QStringList()<<"[23:20] (Ignored  if master address width >= 28 bits)"<<"Here I can put any version"<<"24"<<"48");
     m_pTexComboBoxPosition->addItems(list2);
     QStringList list3=(QStringList()<<"Indirect address sourced from register(s) in slot 2 space "<<"Here I can put any version1"<<"24"<<"48");
     m_pTexComboBoxIndirect->addItems(list3);
     pLableAddresNumber->setText("Number of address bymaster:");
     pLableAddrescPosition->setText("Position in slave address  of upper 4 bits  of master address:");
     pLableAddresIndirect->setText("Indirect Addressing:");

     m_pGetAddresConfig               = new QGroupBox("Address Configuration");
     QGridLayout*    pAddressGrLayout = new  QGridLayout();
     pAddressGrLayout->addWidget(pLableAddresNumber ,0 ,0);
     pAddressGrLayout->addWidget(pLableAddrescPosition ,1 ,0);
     pAddressGrLayout->addWidget(pLableAddresIndirect ,2 ,0);
     pAddressGrLayout->addWidget(m_pTexComboBoxNumber ,0 ,1);
     pAddressGrLayout->addWidget(m_pTexComboBoxPosition ,1 ,1);
     pAddressGrLayout->addWidget(m_pTexComboBoxIndirect ,2 ,1);
     pAddressGrLayout->setContentsMargins(10,22,10,10);
     pAddressGrLayout->addItem(m_pHorizontalSpacer,3,4);
     m_pGetAddresConfig-> setLayout(pAddressGrLayout);
     m_pGetAddresConfig->setStyleSheet("QGroupBox {font: bold; border: 1px solid silver;\
             border-radius: 0px;margin-top: 6px;}QGroupBox::title {\
             subcontrol-origin: margin;left: 7px;padding: 0px 0px 0px 0px; }");
}

void CorAPB3Configurator::createHorTestbenchLayout()
{
    m_pComboBoxTestbench = new  QComboBox();
    QStringList list=(QStringList()<<"User"<<"use1"<<"User2"<<"User3");
    m_pComboBoxTestbench->addItems(list);

    QHBoxLayout*        pHorTestbenchLayout = new QHBoxLayout;
    pHorTestbenchLayout->addWidget(m_pLableTestB);
    pHorTestbenchLayout->addWidget(m_pComboBoxTestbench);
    m_pTestBench->setLayout(pHorTestbenchLayout);
    pHorTestbenchLayout->addItem(m_pHorizontalSpacer);
}

void CorAPB3Configurator::createLicenseGrubBox()
{

    QHBoxLayout*    horizLayoutLicense =  new QHBoxLayout;
    QLabel*	      pLableLicence      =  new QLabel("License:");
    m_pLicenseWidges                   =  new QWidget();
    m_pRButtonObfuscat	             =  new QRadioButton("Obfuscate");
    m_pRButtonRTL                      =  new QRadioButton("RTL");

    horizLayoutLicense->addWidget(pLableLicence);
    horizLayoutLicense->addWidget(m_pRButtonObfuscat);
    horizLayoutLicense->addWidget(m_pRButtonRTL);
    horizLayoutLicense->addItem(m_pHorizontalSpacer);
    horizLayoutLicense-> setContentsMargins(0,0,0,140);
    m_pLicenseWidges->setLayout(horizLayoutLicense);
}

void CorAPB3Configurator::createVerButtonlLayout()
{
    QPushButton*   pOkPushbutton                 = new QPushButton("save");
    QPushButton*   pCancelPushButton             = new QPushButton("Cancel");
    QPushButton*   pHelpPushbutton               = new QPushButton("Hellp");
    QHBoxLayout*   pVerButtonlLayout             = new QHBoxLayout;

    pVerButtonlLayout->addWidget(pHelpPushbutton);
    pVerButtonlLayout->addItem(m_pHorizontalSpacer);
    pVerButtonlLayout->addWidget(pOkPushbutton);
    pVerButtonlLayout->addWidget(pCancelPushButton);
    m_pGetHelp->setLayout(pVerButtonlLayout);
    QObject::connect(pOkPushbutton, SIGNAL(clicked(bool)),this, SLOT (saveSlot()));
}

void CorAPB3Configurator::createTabWidVerLyout()
{
    QWidget*     pTabConfiguration     = new QWidget;
    QVBoxLayout* pTabLayout            = new QVBoxLayout();

    pTabLayout->addWidget(m_pGetDataConfig);
    pTabLayout->addWidget(m_pGetAddresConfig);
    pTabLayout->addWidget(m_pGetAllocateMemory);
    pTabLayout->addWidget(m_pGetEnablMemory);
    pTabLayout->addWidget(m_pTestBench);
    pTabLayout->addWidget(m_pLicenseWidges);
    pTabLayout->setContentsMargins(10,5,10,5);
    m_pTabWidges->addTab(pTabConfiguration,"Configuration");
    pTabConfiguration->setLayout(pTabLayout);
}

void CorAPB3Configurator::createDialogLayout()
{

    QVBoxLayout* pDialogLayout = new QVBoxLayout;
    pDialogLayout->addWidget(m_pTitleBanner);
    pDialogLayout->addWidget(m_pTabWidges);
    pDialogLayout->addWidget(m_pGetHelp);
    this->setLayout(pDialogLayout);
}


CorAPB3Configurator::CorAPB3Configurator()
    : QWidget()

{
    m_pHorizontalSpacer =new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    createTitlBaner();
    createTabConfigurator();
    createDataWidthConfiguration();
    createAddressConfigFontComBox();
    createAllocateMemryCheckBoxs();
    createEnableAPBArrayCheckBoxs();
    createTestbenchGrup();
    createLicenseGrubBox();
    createHelpGrBox();
    createTabWidVerLyout();
    createDialogLayout();
    JsonReadeAndSaved(QString::fromStdString("frst.json"))  ; 


}


int main (int ag ,char*agc [])

{

  QApplication app(ag,agc);
  CorAPB3Configurator ok;
  ok.show();

  return  app.exec();
}

