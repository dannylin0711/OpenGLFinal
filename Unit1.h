//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "GLCtrl.h"
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TGLBox *GLBox1;
    TRadioButton *SingleMode;
    TRadioButton *MultiMode;
    TGroupBox *RotateGroup;
    TScrollBar *XRotateScrollBar;
    TLabel *XRotateLabel;
    TScrollBar *YRotateScrollBar;
    TLabel *YRotateLabel;
    TScrollBar *ZRotateScrollBar;
    TLabel *ZRotateLabel;
    TButton *ResetRotateButton;
    TGroupBox *MoveGroup;
    TLabel *XMoveLabel;
    TLabel *YMoveLabel;
    TLabel *ZMoveLable;
    TScrollBar *XMoveScrollBar;
    TScrollBar *YMoveScrollBar;
    TScrollBar *ZMoveScrollBar;
    TButton *ResetMoveButton;
    TGroupBox *AmountGroup;
    TGroupBox *ScaleGroup;
    TLabel *XScaleLabel;
    TLabel *YScaleLabel;
    TLabel *ZScaleLable;
    TScrollBar *XScaleScrollBar;
    TScrollBar *YScaleScrollBar;
    TScrollBar *ZScaleScrollBar;
    TButton *ResetScaleGroup;
        TCheckBox *ScaleCheckBox;
    TLabel *XRotateAmount;
    TLabel *YRotateAmount;
    TLabel *ZRotateAmount;
    TLabel *XMoveAmount;
    TLabel *YMoveAmount;
    TLabel *ZMoveAmount;
    TLabel *XScaleAmount;
    TLabel *YScaleAmount;
    TLabel *ZScaleAmount;
    TGroupBox *LightGroup;
    TCheckBox *redLightCheckBox;
    TCheckBox *greenLightCheckBox;
    TCheckBox *blueLightCheckBox;
    TGroupBox *ModelGroup;
    TRadioButton *colorcubeRadio;
    TRadioButton *readfileRadio;
    TGroupBox *ShadingModeGroup;
    TRadioButton *smoothRadio;
    TRadioButton *flatRadio;
    TGroupBox *TextureGroup;
    TRadioButton *goldRadio;
    TRadioButton *pewterRadio;
    TRadioButton *silverRadio;
    TRadioButton *disableMaterialRadio;
    TOpenDialog *modelOpener;
    TGroupBox *polygonMode;
    TRadioButton *fillRadio;
    TRadioButton *lineRadio;
    void __fastcall init(TObject *Sender);
    void __fastcall graphicDraw(TObject *Sender);
    
    void __fastcall XRotateScrollBarChange(TObject *Sender);
    void __fastcall YRotateScrollBarChange(TObject *Sender);
    void __fastcall ZRotateScrollBarChange(TObject *Sender);
    void __fastcall XMoveScrollBarChange(TObject *Sender);
    void __fastcall YMoveScrollBarChange(TObject *Sender);
    void __fastcall ZMoveScrollBarChange(TObject *Sender);
    void __fastcall XScaleScrollBarChange(TObject *Sender);
    void __fastcall YScaleScrollBarChange(TObject *Sender);
    void __fastcall ZScaleScrollBarChange(TObject *Sender);
    void __fastcall ResetRotateButtonClick(TObject *Sender);
    void __fastcall ResetMoveButtonClick(TObject *Sender);
    void __fastcall ResetScaleGroupClick(TObject *Sender);
    void __fastcall ChangeSingleMode(TObject *Sender);
    void __fastcall ChangeMultiMode(TObject *Sender);
    void __fastcall checkScale(TObject *Sender);
    void __fastcall readFileClicked(TObject *Sender);
    void __fastcall redLightCheckBoxClick(TObject *Sender);
    void __fastcall greenLightCheckBoxClick(TObject *Sender);
    void __fastcall blueLightCheckBoxClick(TObject *Sender);
    void __fastcall colorcubeRadioClick(TObject *Sender);
    void __fastcall disableMaterialRadioClick(TObject *Sender);
    void __fastcall goldRadioClick(TObject *Sender);
    void __fastcall pewterRadioClick(TObject *Sender);
    void __fastcall silverRadioClick(TObject *Sender);
    void __fastcall smoothRadioClick(TObject *Sender);
    void __fastcall flatRadioClick(TObject *Sender);
    void __fastcall fillRadioClick(TObject *Sender);
    void __fastcall lineRadioClick(TObject *Sender);


private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
