#ifndef FINDDIALOG_H
#define FINDDIALOG_H
#include <QObject>
#include <QtWidgets/QComboBox>

#include <QtWidgets/QWidget>
#include <QtWidgets/QCheckBox>
#include<QtWidgets/QDialog>
#include<iostream>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include<QTextStream>
#include<QJsonDocument>
#include<QFile>
#include <string>
#include<QJsonObject>
#include <QtWidgets/QTabWidget>
#include <QLabel>
#include <QtWidgets/QGroupBox>
class myChecBox : public QCheckBox
{
    Q_OBJECT

    public :

        myChecBox()
            : QCheckBox()
        {
        }
        myChecBox(QString a)
            : QCheckBox(a)
        {

        }
        void mysetText(std::string a);

    public slots:
            void mySlotChekBox(bool);
};


class CorAPB3Configurator : public QWidget
{
    Q_OBJECT

    public slots:
        void saveSlot();

    public :
        CorAPB3Configurator();

        std::string   getDataBusWidthMemory();///APB_data_bus();
        std::string   getNuberBitsMasterMemory();//get
        std::string   getPositionUpper4BitsMemory();
        std::string   getIndirectAddresMemory();
        std::string   getTestBenchMemory();
        std::string   getLicenseMemory();
        QJsonObject   JsonReadeAndSaved( QString in);
        QJsonArray    getAllocateMemory();
        QJsonArray    getEenableAPBMemory();
        QJsonArray    getiDisableAPBMemory();


        void createTabConfigurator();
        void createTitlBaner();
        void createDataWidthConfiguration();
        void createAllocateMemryCheckBoxs();
        void createEnableAPBArrayCheckBoxs();
        void createTestbenchGrup();
        void createHelpGrBox();
        void createAddressConfigFontComBox();
        void createHorTestbenchLayout();
        void createLicenseGrubBox();
        void createVerButtonlLayout();
        void createTabWidVerLyout();
        void createDialogLayout();
    private:
    QLabel*         m_pLableTestB;
    QWidget*        m_pLicenseWidges;
    QWidget*        m_pTitleBanner;
    QWidget*        m_pTestBench;
    QComboBox*      m_pTexComboBoxNumber;
    QComboBox*      m_pTexComboBoxPosition;
    QComboBox*      m_pTexComboBoxIndirect;
    QComboBox*      m_pComboBoxTestbench;
    QGroupBox*      m_pGetHelp;
    QGroupBox*      m_pGetEnablMemory;
    QGroupBox*      m_pGetAllocateMemory;
    QGroupBox*      m_pGetDataConfig;
    QGroupBox*      m_pGetAddresConfig;
    QJsonArray*     m_pArrAllocateMemory;
    QTabWidget*     m_pTabWidges;
    QSpacerItem*    m_pHorizontalSpacer;
    QRadioButton*   m_pRButton32Bit;
    QRadioButton*   m_pRButton16Bit;
    QRadioButton*   m_pRButton8Bit;
    QRadioButton*   m_pRButtonObfuscat;
    QRadioButton*   m_pRButtonRTL;
    QVarLengthArray <QCheckBox*,16>* mChBpArryAllocate;
    QVarLengthArray <QCheckBox*,16>* mChBpArryRnelARBwSlot;

    /*

       QVarLengthArray <QCheckBox*,16>& m_arrOfpChB = *m_pArrOfpChB;
       QCheckBox* pChB = m_arrOfpChB[i];
       QCheckBox& chB = *pChB;
     */
#endif // FINDDIALOG_H


};

