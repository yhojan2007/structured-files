//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <fstream>          // libreria para manejar archibos
#include <cmath>

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *Edit1;
	TButton *Button1;
	TEdit *Edit2;
	TEdit *Edit3;
	TEdit *Edit4;
	TEdit *Edit5;
	TButton *Button2;
	TMainMenu *MainMenu1;
	TLabel *Label4;
	TButton *Button4;
	TMenuItem *MOdificasiones1;
	TMenuItem *MOdificasiones2;
	TMenuItem *cambiaraminucculasNOmdelosabril1;
	TMenuItem *eliminarlosregquetenganmasde2oensunombre1;
	TButton *Button5;
	TLabel *Label5;
	TEdit *Edit6;
	TButton *Button6;
	TButton *Button7;
	TButton *Button8;
	TButton *Button9;
	TMenuItem *LISTADOS1;
	TMenuItem *LISTADOS2;
	TMenuItem *listadodeindicepornombre1;
	TMenuItem *ORDENAMINTO1;
	TMenuItem *ORDENAMINTO2;
	TMenuItem *listadodemanetadesensendente1;
	TMenuItem *modelosdeexamen1;
	TMenuItem *actualizarlosnombreala1raMayuscula1;
	TMenuItem *listadodelosregqueempizenen501;
	TMenuItem *aumentar1diaalosreg1;
	TButton *Button11;
	TMenuItem *N111;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Edit1Exit(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall MOdificasiones2Click(TObject *Sender);
	void __fastcall cambiaraminucculasNOmdelosabril1Click(TObject *Sender);
	void __fastcall eliminarlosregquetenganmasde2oensunombre1Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall LISTADOS2Click(TObject *Sender);
	void __fastcall ORDENAMINTO2Click(TObject *Sender);
	void __fastcall listadodeindicepornombre1Click(TObject *Sender);
	void __fastcall listadodemanetadesensendente1Click(TObject *Sender);
	void __fastcall actualizarlosnombreala1raMayuscula1Click(TObject *Sender);
	void __fastcall listadodelosregqueempizenen501Click(TObject *Sender);
	void __fastcall aumentar1diaalosreg1Click(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall N111Click(TObject *Sender);


private:	// User declarations
	 AnsiString ruta,nom,nomCod,nomNom;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
    long int BusBinariaIdx(Word codB);
}; \
struct TFecha {
	byte dia;
	byte mes;
	Word ano;
};   //4 byte
struct RegAlumnoAnt {
	Word cod;
	char nom[22];
	TFecha fecha;
};  //28 byte
#pragma pack(1) //para tener el tamano exacto en byte de la structura
struct RegAlumno {
	char marca; //para el borrado logico
	Word cod;
	char nom[30];
	TFecha fecha;
	Cardinal telefono;
};   // 41 bytes
struct RegIdxCod {
	Word cod;
	Cardinal ref;
};    //byte 6
struct RegIdxNom {
	char nom[30];   //30bytes
	Cardinal ref;  //4bytes
};  //34 bytes


//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
