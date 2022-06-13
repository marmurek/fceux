// LcdCompZapperConf.h
//

#pragma once

#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QTimer>
#include <QTabBar>
#include <QGroupBox>
#include <QPainter>
#include <QTreeView>
#include <QTreeWidget>
#include <QPropertyAnimation>

#include "Qt/main.h"
#include "Qt/input.h"

class LcdCompZapperConfigButton_t : public QPushButton
{
public:
	LcdCompZapperConfigButton_t(int i);

protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

	int idx;
};

class LcdCompZapperConfigHotKey_t : public QPushButton
{
public:
	LcdCompZapperConfigHotKey_t( int idx, gamepad_function_key_t *k );

	void setCaptureState(bool s){ captureState = s; };

	void setKeyNameLbl( QLineEdit *lbl );
protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

	int idx;
	QLineEdit *keySeqLbl;
	gamepad_function_key_t *k;
	bool captureState;
};

class LcdHotKeySelectDialog_t : public QDialog
{
	Q_OBJECT

public:
	LcdHotKeySelectDialog_t( QWidget *parent = 0);
	~LcdHotKeySelectDialog_t(void);

	int  getSelHotKey(void){ return hotKeyIdx; };
protected:
	void closeEvent(QCloseEvent *bar);

	QTreeWidget *tree;
	QPushButton *okButton;
	QPushButton *cancelButton;

	int   hotKeyIdx;

public slots:
	void closeWindow(void);
private slots:
	void acceptCB(void);
	void rejectCB(void);
	void hotkeyItemClicked(QTreeWidgetItem *item, int column);
};

class LcdCompZapperFuncConfigDialog : public QDialog
{
	Q_OBJECT

public:
	LcdCompZapperFuncConfigDialog( int portNum, gamepad_function_key_t *fk, QWidget *parent = 0);
	~LcdCompZapperFuncConfigDialog(void);

protected:
	void closeEvent(QCloseEvent *bar);

	void changeButton(int x);

	QLineEdit *btnLbl[2];
	QLineEdit *keySeqLbl[2];

	LcdCompZapperConfigButton_t  *b[2];
	LcdCompZapperConfigHotKey_t  *hk[2];
	gamepad_function_key_t *k;

	int  portNum;
	int  buttonConfigStatus;
	bool editMode;

public slots:
	void closeWindow(void);
private slots:
	void acceptCB(void);
	void rejectCB(void);
	void changeButton0(void);
	void changeButton1(void);
	void changeKeySeq0(void);
	void changeKeySeq1(void);
	void clearButton0(void);
	void clearButton1(void);
	void clearButton2(void);
	void clearButton3(void);
};


class LcdCompZapperConfDialog_t : public QDialog
{
	Q_OBJECT

public:
	LcdCompZapperConfDialog_t(QWidget *parent = 0);
	~LcdCompZapperConfDialog_t(void);

protected:
	QWidget *mainWidget;
	QTimer *inputTimer;
	QComboBox *portSel;
	QComboBox *devSel;
	QComboBox *mapSel;
	QComboBox *profSel;
	QLabel *guidLbl;
	QLabel *mapMsg;
	QLabel *keyName[2];
	QLabel *keyState[2];
	LcdCompZapperConfigButton_t *button[2];
	QTabBar *confTabBar;

	QPushButton *newKeyBindBtn;
	QPushButton *editKeyBindBtn;
	QPushButton *delKeyBindBtn;
	QTreeWidget *keyBindTree;

	int portNum;
	int configIndex;
	int buttonConfigStatus;
	int changeSeqStatus; // status of sequentally changing buttons mechanism
						 //    0 - we can start new change process
						 // 1-10 - changing in progress
						 //   -1 - changing is aborted

	void changeButton(int port, int button);
	void clearButton(int port, int button);
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	void closeEvent(QCloseEvent *bar);

	void refreshKeyBindTree( bool reset = false );

private:
	void updateCntrlrDpy(void);
	void createNewProfile(const char *name);
	void loadMapList(void);
	void saveConfig(void);
	int  promptToSave(void);
	void openFuncEditWindow( int mode, gamepad_function_key_t *k );

public slots:
	void closeWindow(void);
private slots:
	void changeButton0(void);
	void changeButton1(void);
	void clearButton0(void);
	void clearButton1(void);
	void clearAllCallback(void);
	void portSelect(int index);
	void deviceSelect(int index);
	void newProfileCallback(void);
	void loadProfileCallback(void);
	void saveProfileCallback(void);
	void deleteProfileCallback(void);
	void updatePeriodic(void);
	void changeSequentallyCallback(void);
	void newKeyBindingCallback(void);
	void editKeyBindingCallback(void);
	void delKeyBindingCallback(void);
	void saveAll(void);
};

int openLcdCompZapperConfWindow(QWidget *parent);

int closeLcdCompZapperConfWindow(void);
