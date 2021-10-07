object Form1: TForm1
  Left = 551
  Top = 153
  Width = 956
  Height = 844
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object GLBox1: TGLBox
    Left = 0
    Top = 0
    Width = 945
    Height = 585
    Cursor = crDrag
    Enabled = False
    GLColorBits = 32
    OnGLInit = init
    OnGLDraw = graphicDraw
  end
  object RotateGroup: TGroupBox
    Left = 304
    Top = 592
    Width = 209
    Height = 177
    Caption = #26059#36681
    TabOrder = 1
    object XRotateLabel: TLabel
      Left = 8
      Top = 24
      Width = 19
      Height = 13
      Caption = 'X'#36600
    end
    object YRotateLabel: TLabel
      Left = 8
      Top = 64
      Width = 19
      Height = 13
      Caption = 'Y'#36600
    end
    object ZRotateLabel: TLabel
      Left = 8
      Top = 104
      Width = 19
      Height = 13
      Caption = 'Z'#36600
    end
    object XRotateAmount: TLabel
      Left = 96
      Top = 24
      Width = 6
      Height = 13
      Alignment = taCenter
      Caption = '0'
    end
    object YRotateAmount: TLabel
      Left = 96
      Top = 64
      Width = 6
      Height = 13
      Alignment = taCenter
      Caption = '0'
    end
    object ZRotateAmount: TLabel
      Left = 96
      Top = 104
      Width = 6
      Height = 13
      Alignment = taCenter
      Caption = '0'
    end
    object XRotateScrollBar: TScrollBar
      Left = 8
      Top = 40
      Width = 185
      Height = 17
      HelpType = htKeyword
      Max = 180
      Min = -180
      PageSize = 0
      TabOrder = 0
      OnChange = XRotateScrollBarChange
    end
    object YRotateScrollBar: TScrollBar
      Left = 8
      Top = 80
      Width = 185
      Height = 17
      Max = 180
      Min = -180
      PageSize = 0
      TabOrder = 1
      OnChange = YRotateScrollBarChange
    end
    object ZRotateScrollBar: TScrollBar
      Left = 8
      Top = 120
      Width = 185
      Height = 17
      Max = 180
      Min = -180
      PageSize = 0
      TabOrder = 2
      OnChange = ZRotateScrollBarChange
    end
    object ResetRotateButton: TButton
      Left = 112
      Top = 144
      Width = 81
      Height = 25
      Caption = #37325#32622
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS UI Gothic'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = ResetRotateButtonClick
    end
  end
  object MoveGroup: TGroupBox
    Left = 520
    Top = 592
    Width = 209
    Height = 177
    Caption = #24179#31227
    TabOrder = 2
    object XMoveLabel: TLabel
      Left = 8
      Top = 24
      Width = 19
      Height = 13
      Caption = 'X'#36600
    end
    object YMoveLabel: TLabel
      Left = 8
      Top = 64
      Width = 19
      Height = 13
      Caption = 'Y'#36600
    end
    object ZMoveLable: TLabel
      Left = 8
      Top = 104
      Width = 19
      Height = 13
      Caption = 'Z'#36600
    end
    object XMoveAmount: TLabel
      Left = 96
      Top = 24
      Width = 6
      Height = 13
      Alignment = taCenter
      Caption = '0'
    end
    object YMoveAmount: TLabel
      Left = 96
      Top = 64
      Width = 6
      Height = 13
      Alignment = taCenter
      Caption = '0'
    end
    object ZMoveAmount: TLabel
      Left = 96
      Top = 104
      Width = 6
      Height = 13
      Alignment = taCenter
      Caption = '0'
    end
    object XMoveScrollBar: TScrollBar
      Left = 8
      Top = 40
      Width = 185
      Height = 17
      HelpType = htKeyword
      Max = 3000
      Min = -3000
      PageSize = 0
      TabOrder = 0
      OnChange = XMoveScrollBarChange
    end
    object YMoveScrollBar: TScrollBar
      Left = 8
      Top = 80
      Width = 185
      Height = 17
      Max = 3000
      Min = -3000
      PageSize = 0
      TabOrder = 1
      OnChange = YMoveScrollBarChange
    end
    object ZMoveScrollBar: TScrollBar
      Left = 8
      Top = 120
      Width = 185
      Height = 17
      Max = 3000
      Min = -3000
      PageSize = 0
      TabOrder = 2
      OnChange = ZMoveScrollBarChange
    end
    object ResetMoveButton: TButton
      Left = 112
      Top = 144
      Width = 81
      Height = 25
      Caption = #37325#32622
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS UI Gothic'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = ResetMoveButtonClick
    end
  end
  object AmountGroup: TGroupBox
    Left = 8
    Top = 592
    Width = 289
    Height = 41
    Caption = #27169#24335
    TabOrder = 3
    object SingleMode: TRadioButton
      Left = 16
      Top = 16
      Width = 57
      Height = 17
      Caption = #21934#19968
      Checked = True
      TabOrder = 0
      TabStop = True
      OnClick = ChangeSingleMode
    end
    object MultiMode: TRadioButton
      Left = 176
      Top = 16
      Width = 57
      Height = 17
      Caption = #22810#20491
      TabOrder = 1
      OnClick = ChangeMultiMode
    end
  end
  object ScaleGroup: TGroupBox
    Left = 736
    Top = 592
    Width = 209
    Height = 177
    Caption = #32302#25918
    TabOrder = 4
    object XScaleLabel: TLabel
      Left = 8
      Top = 24
      Width = 19
      Height = 13
      Caption = 'X'#36600
    end
    object YScaleLabel: TLabel
      Left = 8
      Top = 64
      Width = 19
      Height = 13
      Caption = 'Y'#36600
    end
    object ZScaleLable: TLabel
      Left = 8
      Top = 104
      Width = 19
      Height = 13
      Caption = 'Z'#36600
    end
    object XScaleAmount: TLabel
      Left = 96
      Top = 24
      Width = 18
      Height = 13
      Alignment = taCenter
      Caption = '100'
    end
    object YScaleAmount: TLabel
      Left = 96
      Top = 64
      Width = 18
      Height = 13
      Alignment = taCenter
      Caption = '100'
    end
    object ZScaleAmount: TLabel
      Left = 96
      Top = 104
      Width = 18
      Height = 13
      Alignment = taCenter
      Caption = '100'
    end
    object XScaleScrollBar: TScrollBar
      Left = 8
      Top = 40
      Width = 185
      Height = 17
      HelpType = htKeyword
      Max = 500
      Min = -500
      PageSize = 0
      Position = 100
      TabOrder = 0
      OnChange = XScaleScrollBarChange
    end
    object YScaleScrollBar: TScrollBar
      Left = 8
      Top = 80
      Width = 185
      Height = 17
      Max = 500
      Min = -500
      PageSize = 0
      Position = 100
      TabOrder = 1
      OnChange = YScaleScrollBarChange
    end
    object ZScaleScrollBar: TScrollBar
      Left = 8
      Top = 120
      Width = 185
      Height = 17
      Max = 500
      Min = -500
      PageSize = 0
      Position = 100
      TabOrder = 2
      OnChange = ZScaleScrollBarChange
    end
    object ResetScaleGroup: TButton
      Left = 112
      Top = 144
      Width = 81
      Height = 25
      Caption = #37325#32622
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS UI Gothic'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = ResetScaleGroupClick
    end
    object ScaleCheckBox: TCheckBox
      Left = 8
      Top = 144
      Width = 97
      Height = 17
      Caption = #31561#27604#20363
      TabOrder = 4
      OnClick = checkScale
    end
  end
  object LightGroup: TGroupBox
    Left = 8
    Top = 632
    Width = 289
    Height = 49
    Caption = #29128#20809
    TabOrder = 5
    object redLightCheckBox: TCheckBox
      Left = 32
      Top = 24
      Width = 49
      Height = 17
      Caption = #32005#29128
      Checked = True
      State = cbChecked
      TabOrder = 0
      OnClick = redLightCheckBoxClick
    end
    object greenLightCheckBox: TCheckBox
      Left = 120
      Top = 24
      Width = 57
      Height = 17
      Caption = #32160#29128
      Checked = True
      State = cbChecked
      TabOrder = 1
      OnClick = greenLightCheckBoxClick
    end
    object blueLightCheckBox: TCheckBox
      Left = 208
      Top = 24
      Width = 49
      Height = 17
      Caption = #34253#29128
      Checked = True
      State = cbChecked
      TabOrder = 2
      OnClick = blueLightCheckBoxClick
    end
  end
  object ModelGroup: TGroupBox
    Left = 8
    Top = 680
    Width = 145
    Height = 89
    Caption = #27169#22411#21450#22810#37002#24418#27169#24335
    TabOrder = 6
    object colorcubeRadio: TRadioButton
      Left = 16
      Top = 24
      Width = 113
      Height = 17
      Caption = #31435#26041#39636
      Checked = True
      TabOrder = 0
      TabStop = True
      OnClick = colorcubeRadioClick
    end
    object readfileRadio: TRadioButton
      Left = 16
      Top = 56
      Width = 113
      Height = 17
      Caption = #35712#27284
      TabOrder = 1
      OnClick = readFileClicked
    end
  end
  object ShadingModeGroup: TGroupBox
    Left = 160
    Top = 680
    Width = 137
    Height = 89
    Caption = #22635#33394#27169#24335
    TabOrder = 7
    object smoothRadio: TRadioButton
      Left = 16
      Top = 24
      Width = 113
      Height = 17
      Caption = #28472#23652
      Checked = True
      TabOrder = 0
      TabStop = True
      OnClick = smoothRadioClick
    end
    object flatRadio: TRadioButton
      Left = 16
      Top = 56
      Width = 113
      Height = 17
      Caption = #32020#33394
      TabOrder = 1
      OnClick = flatRadioClick
    end
  end
  object TextureGroup: TGroupBox
    Left = 8
    Top = 768
    Width = 505
    Height = 41
    Caption = #26448#36074
    TabOrder = 8
    object goldRadio: TRadioButton
      Left = 24
      Top = 16
      Width = 113
      Height = 17
      Caption = #37329
      Checked = True
      TabOrder = 0
      TabStop = True
      OnClick = goldRadioClick
    end
    object pewterRadio: TRadioButton
      Left = 144
      Top = 16
      Width = 113
      Height = 17
      Caption = #37675
      TabOrder = 1
      OnClick = pewterRadioClick
    end
    object silverRadio: TRadioButton
      Left = 264
      Top = 16
      Width = 113
      Height = 17
      Caption = #25291#20809#36942#30340#37504
      TabOrder = 2
      OnClick = silverRadioClick
    end
    object disableMaterialRadio: TRadioButton
      Left = 384
      Top = 16
      Width = 113
      Height = 17
      Caption = #28961
      TabOrder = 3
      OnClick = disableMaterialRadioClick
    end
  end
  object polygonMode: TGroupBox
    Left = 520
    Top = 768
    Width = 425
    Height = 41
    Caption = #22810#37002#24418#27169#24335
    TabOrder = 9
    object fillRadio: TRadioButton
      Left = 64
      Top = 16
      Width = 113
      Height = 17
      Caption = #22635#28415
      Checked = True
      TabOrder = 0
      TabStop = True
      OnClick = fillRadioClick
    end
    object lineRadio: TRadioButton
      Left = 256
      Top = 16
      Width = 113
      Height = 17
      Caption = #32218#26781
      TabOrder = 1
      OnClick = lineRadioClick
    end
  end
  object modelOpener: TOpenDialog
    Left = 192
    Top = 104
  end
end
