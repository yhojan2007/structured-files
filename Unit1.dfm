object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Archivos Estructurados'
  ClientHeight = 518
  ClientWidth = 750
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Menu = MainMenu1
  OnCreate = FormCreate
  TextHeight = 15
  object Label1: TLabel
    Left = 24
    Top = 109
    Width = 63
    Height = 28
    Caption = 'codigo'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 24
    Top = 157
    Width = 76
    Height = 28
    Caption = 'Nombre'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 24
    Top = 205
    Width = 53
    Height = 28
    Caption = 'Fecha'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object Label4: TLabel
    Left = 280
    Top = 32
    Width = 177
    Height = 37
    Caption = 'ABM alumnos'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object Label5: TLabel
    Left = 18
    Top = 264
    Width = 82
    Height = 28
    Caption = 'Telefono'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object Edit1: TEdit
    Left = 128
    Top = 117
    Width = 121
    Height = 23
    TabOrder = 0
    Text = '0'
    OnExit = Edit1Exit
  end
  object Button1: TButton
    Left = 573
    Top = 456
    Width = 169
    Height = 41
    Caption = 'ver bytes de cada campo'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Edit2: TEdit
    Left = 128
    Top = 165
    Width = 569
    Height = 23
    TabOrder = 2
  end
  object Edit3: TEdit
    Left = 128
    Top = 213
    Width = 49
    Height = 23
    TabOrder = 3
  end
  object Edit4: TEdit
    Left = 183
    Top = 213
    Width = 49
    Height = 23
    TabOrder = 4
  end
  object Edit5: TEdit
    Left = 238
    Top = 213
    Width = 121
    Height = 23
    TabOrder = 5
  end
  object Button2: TButton
    Left = 18
    Top = 327
    Width = 113
    Height = 41
    Caption = 'Guardar'
    TabOrder = 6
    OnClick = Button2Click
  end
  object Button4: TButton
    Left = 18
    Top = 374
    Width = 113
    Height = 41
    Caption = 'Listado'
    TabOrder = 7
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 18
    Top = 485
    Width = 144
    Height = 25
    Caption = 'modificar la structura'
    Enabled = False
    TabOrder = 8
    OnClick = Button5Click
  end
  object Edit6: TEdit
    Left = 128
    Top = 264
    Width = 193
    Height = 23
    TabOrder = 9
  end
  object Button6: TButton
    Left = 18
    Top = 421
    Width = 113
    Height = 46
    Caption = 'Eliminado Logico'
    TabOrder = 10
    OnClick = Button6Click
  end
  object Button7: TButton
    Left = 218
    Top = 456
    Width = 179
    Height = 41
    Caption = 'listado completo'
    TabOrder = 11
    OnClick = Button7Click
  end
  object Button8: TButton
    Left = 218
    Top = 327
    Width = 179
    Height = 46
    Caption = 'crear indice por codigo'
    TabOrder = 12
    OnClick = Button8Click
  end
  object Button9: TButton
    Left = 218
    Top = 391
    Width = 179
    Height = 50
    Caption = 'crear indice por nombre'
    TabOrder = 13
    OnClick = Button9Click
  end
  object MainMenu1: TMainMenu
    Left = 56
    Top = 48
    object MOdificasiones1: TMenuItem
      Caption = 'Modificasiones'
      object MOdificasiones2: TMenuItem
        Caption = 'cambiar a mayusculas los nombres'
        OnClick = MOdificasiones2Click
      end
      object cambiaraminucculasNOmdelosabril1: TMenuItem
        Caption = 'cambiar a minusculas Nombres de los abril'
        OnClick = cambiaraminucculasNOmdelosabril1Click
      end
      object eliminarlosregquetenganmasde2oensunombre1: TMenuItem
        Caption = 'eliminar los reg que tengan mas de 2 "o" en su nombre'
        OnClick = eliminarlosregquetenganmasde2oensunombre1Click
      end
    end
    object LISTADOS1: TMenuItem
      Caption = 'LISTADOS'
      object LISTADOS2: TMenuItem
        Caption = 'listado de indice por codigo'
        OnClick = LISTADOS2Click
      end
      object listadodeindicepornombre1: TMenuItem
        Caption = 'listado de indice por nombre'
        OnClick = listadodeindicepornombre1Click
      end
      object listadodemanetadesensendente1: TMenuItem
        Caption = 'listado de maneta desensendente'
        OnClick = listadodemanetadesensendente1Click
      end
    end
    object ORDENAMINTO1: TMenuItem
      Caption = 'ORDENAMINTO'
      object ORDENAMINTO2: TMenuItem
        Caption = 'selection short de reg ee indice por codigo'
        OnClick = ORDENAMINTO2Click
      end
    end
    object modelosdeexamen1: TMenuItem
      Caption = 'modelos de examen'
      object actualizarlosnombreala1raMayuscula1: TMenuItem
        Caption = 'actualizar los nombre a la 1ra Mayuscula'
        OnClick = actualizarlosnombreala1raMayuscula1Click
      end
      object listadodelosregqueempizenen501: TMenuItem
        Caption = 'listado de los reg que empizen en 50'
        OnClick = listadodelosregqueempizenen501Click
      end
      object aumentar1diaalosreg1: TMenuItem
        Caption = 'aumentar 1 dia a los reg'
        OnClick = aumentar1diaalosreg1Click
      end
    end
  end
end
