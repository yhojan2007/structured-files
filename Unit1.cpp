//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <vector>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Edit1->Text = sizeof(TFecha);
	Edit2->Text = sizeof(RegAlumno);
	Edit3->Text = sizeof(byte);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
   ruta= "D:\\c++ 12\\archibos estructurados\\";
   nom=ruta + "Alumnos.dat";
   nomCod=ruta+"Alumnoscod.idx";
   nomNom=ruta+"AlumnosNom.idx";
   fstream f(nom.c_str(),ios::binary|ios::in);

   if (f.fail()) {
	   f.open(nom.c_str(),ios::binary|ios::out);
   }
   f.close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	RegAlumno reg,reg2; bool hallado=false;
	AnsiString aux;
	reg.cod =StrToInt(Edit1->Text);
	aux=Edit2->Text;
	strcpy(reg.nom,aux.c_str());
	reg.fecha.dia =StrToInt(Edit3->Text);
	reg.fecha.mes= StrToInt(Edit4->Text);
	reg.fecha.ano= StrToInt(Edit5->Text);
	reg.telefono= StrToInt(Edit6->Text);
	reg.marca=' ';

	fstream f(nom.c_str(),ios::binary|ios::in|ios::out); //ios::app graba al final de cada registro
	if (!f.fail()) {
		while (!f.eof()&&!hallado) {  // el hallado cambiar por el nuevo apartado de la marca
			f.read((char*)&reg2,sizeof(reg2));
			if (!f.eof()) {
				hallado=(reg2.cod==reg.cod)&&(reg2.marca!='*');
			}
		}
		if (hallado) { //acutualixar un reg
			f.seekg(-sizeof(reg),ios::cur);
			f.write((char*)&reg,sizeof(reg));
		} else {    //adicionar un registro
			f.close();
			f.open(nom.c_str(),ios::binary|ios::app);
			f.write((char*)&reg,sizeof(reg));
		}
		f.close();
		Edit1->Text="0";
		Edit2->Text="";
		Edit3->Text="";
		Edit4->Text="";
		Edit5->Text="";
		Edit6->Text="";
		ShowMessage("datos guardados");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	byte i,x;  AnsiString lin=" ";
    RegAlumno reg;
	fstream f(nom.c_str(),ios::binary|ios::in);
	//leer byte a byte
   /*	for (i=1; i<=28; i++) {
		f.read((char*)&x,1);
		lin=lin+IntToStr(x)+",";
	}
	f.close();
	Edit2->Text=lin; */
	f.read((char*)&reg,sizeof(reg));
	Edit1->Text=reg.cod;
	Edit2->Text=reg.nom;
	Edit3->Text=reg.fecha.dia;
	Edit4->Text=reg.fecha.mes;
	Edit5->Text=reg.fecha.ano;

}
//---------------------------------------------------------------------------
//consulta atraves del condigo
void __fastcall TForm1::Edit1Exit(TObject *Sender)
{
	 RegAlumno reg; Word cod;
	 bool hallado=false;
	 fstream f(nom.c_str(),ios::binary|ios::in);
	 if (!f.fail()) {
		cod=StrToInt(Edit1->Text);
	   /*	while (!f.eof()&&!hallado) {
			f.read((char*)&reg,sizeof(reg));
			if (!f.eof()) {
				hallado=(cod==reg.cod)&&(reg.marca!='*');
			}
		} */
		long int p=BusBinariaIdx(cod);
		if (p>=0) {
			f.seekg(p);
			f.read((char*)&reg,sizeof(reg));
		   Edit2->Text=reg.nom;
		   Edit3->Text=reg.fecha.dia;
		   Edit4->Text=reg.fecha.mes;
		   Edit5->Text=reg.fecha.ano;
		   Edit6->Text=reg.telefono;
		} else {
		   Edit2->Text="";
		   Edit3->Text="";
		   Edit4->Text="";
		   Edit5->Text="";
           Edit6->Text="";
		}
		f.close();
	 }
}
//---------------------------------------------------------------------------
//generar listado de registro en un archivo .csv
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	RegAlumno reg; AnsiString linea,list;
	fstream f(nom.c_str(),ios::binary|ios::in);
	list=ruta+"Listado.csv";
	fstream t(list.c_str(),ios::out);
	if (!f.fail()) {
		while (!f.eof()) {
			f.read((char*)&reg,sizeof(reg));
			if (!f.eof()) {
			  if (reg.marca!='*') { //si no esta borrdo
				linea=IntToStr(reg.cod)+","+reg.nom+","+reg.fecha.dia+","+reg.fecha.mes+","+reg.fecha.ano+","+reg.telefono;
				byte n=linea.Length();
				for (byte i=1; i<=n; i++) {
				  t.put(linea[i]);
				}
				t.put(10);
			  }
			}
		}
		f.close(); t.close();
		ShowMessage("Listado Generado");
	}
}
//---------------------------------------------------------------------------
//cambiar todos los nobres al mayusculas
AnsiString Mayusculas(AnsiString x) {
	AnsiString min="qwertyuiopasdfghjklzxcvbnm";
	AnsiString may="QWERTYUIOPASDFGHJKLZXCVBNM";
	byte i,p,n=x.Length();
	for (i=1; i<=n; i++) {
		p=min.Pos(x[i]);
		if (p>0) {
			x[i]=may[p];
		}
	}
	return x;
}
void __fastcall TForm1::MOdificasiones2Click(TObject *Sender)
{
 RegAlumno reg;
 fstream f(nom.c_str(),ios::binary|ios::in|ios::out);
 if (!f.fail()) {
	while (!f.eof()) {
		f.read((char*)&reg,sizeof(reg));
		if (!f.eof()) {
		  if (reg.marca!='*') {
			AnsiString x=Mayusculas(reg.nom);
			strcpy(reg.nom,x.c_str());
			f.seekg(-sizeof(reg),ios::cur);        //una vez utilzas el seekg el puntero se vuerlve maunula
			f.write((char*)&reg,sizeof(reg));
			f.seekg(sizeof(reg),ios::cur);
			f.seekg(-sizeof(reg),ios::cur);
		  }
		}
	}
	f.close(); ShowMessage("archivo modifivado");
 }
}
//---------------------------------------------------------------------------
//cambiar los ncidos a los de abril
AnsiString Minusculas(AnsiString x) {
	AnsiString min="qwertyuiopasdfghjklzxcvbnm";
	AnsiString may="QWERTYUIOPASDFGHJKLZXCVBNM";
	byte i,p,n=x.Length();
	for (i=1; i<=n; i++) {
		p=may.Pos(x[i]);
		if (p>0) {
			x[i]=min[p];
		}
	}
	return x;
}
void __fastcall TForm1::cambiaraminucculasNOmdelosabril1Click(TObject *Sender)
{
   RegAlumno reg;
 fstream f(nom.c_str(),ios::binary|ios::in|ios::out);
 if (!f.fail()) {
	while (!f.eof()) {
		f.read((char*)&reg,sizeof(reg));
		if (!f.eof()) {
		  if (reg.marca!='*') {
			 if (reg.fecha.mes==4) {
				AnsiString x=Minusculas(reg.nom);
				strcpy(reg.nom,x.c_str());  //cambia un vector a texto
				f.seekg(-sizeof(reg),ios::cur);        //una vez utilzas el seekg el puntero se vuerlve maunula
				f.write((char*)&reg,sizeof(reg));
				f.seekg(sizeof(reg),ios::cur);
				f.seekg(-sizeof(reg),ios::cur);
			 }
		  }
		}
	}
	f.close(); ShowMessage("archivo modifivado");
 }
}
//---------------------------------------------------------------------------
//eliminar registros que tengan mas de 2 o en su nombre
bool Mas2o (AnsiString x){
	AnsiString o="oO";
	byte i,p,n=x.Length(),cont=0;
	for (i=1; i<=n; i++) {
		p=o.Pos(x[i]);
		if (p>0) {
			cont++;
		}
	}
	return cont>=2;
}
void __fastcall TForm1::eliminarlosregquetenganmasde2oensunombre1Click(TObject *Sender)
{
	RegAlumno reg;
	AnsiString nomTemp=ruta+"Temporal.dat";
	fstream f(nom.c_str(),ios::binary|ios::in);
	fstream t(nomTemp.c_str(),ios::binary|ios::out);
	if (!f.fail()) {
		while (!f.eof()) {
			f.read((char*)&reg,sizeof(reg));
			if (!f.eof()) {
				AnsiString aux=reg.nom;
				if (!(Mas2o(aux))) {
					t.write((char*)&reg,sizeof(reg));
				}
			}
		}
		f.close();t.close();
		remove(nom.c_str());
		rename(nomTemp.c_str(),nom.c_str());
        ShowMessage("se eliminaron datos");
	}
}
//---------------------------------------------------------------------------
 //copiar los registros anteriores al nuevo modificado con nuevos campos y apartado
void __fastcall TForm1::Button5Click(TObject *Sender)
{
	RegAlumnoAnt rant; RegAlumno reg;
	fstream fin(nom.c_str(),ios::binary|ios::in);
	fstream fout("Temporal.tmp",ios::binary|ios::out);
	if (!fin.fail()) {
		while (!fin.eof()) {
			fin.read((char*)&rant,sizeof(rant));
			if (!fin.eof()) {
				reg.cod =rant.cod;
				strcpy(reg.nom,rant.nom);
				reg.fecha = rant.fecha;
				reg.telefono=0;
				reg.marca=' ';//no borrado
				fout.write((char*)&reg,sizeof(reg));
			}
		}
		fin.close(); fout.close();
		remove(nom.c_str());
		rename("Temporal.tmp",nom.c_str());
		ShowMessage("archivo copiado a otro modificado los campos");
	}
}
//---------------------------------------------------------------------------
 //elimado logico
void __fastcall TForm1::Button6Click(TObject *Sender)
{
   RegAlumno reg; bool hallado=false; Word codi;
   fstream f(nom.c_str(),ios::binary|ios::in|ios::out);
   if (!f.fail()) {
	codi =StrToInt(Edit1->Text);
	   while (!f.eof()&&!hallado) {
		   f.read((char*)&reg,sizeof(reg));
		   if (!f.eof()) {
			   hallado=(reg.cod==codi)&&(reg.marca!='*');
		   }
	   }
	   if (hallado) {
		  f.seekg(-sizeof(reg),ios::cur);
		  reg.marca='*';
		  f.write((char*)&reg,sizeof(reg));
		  Edit1->Text=0;
		  Edit2->Text="";
		  Edit3->Text="";
		  Edit4->Text="";
		  Edit5->Text="";
		  Edit6->Text="";
		  ShowMessage("Registro eliminado");
	   }
	   f.close();
   }
}
//---------------------------------------------------------------------------
//listado donde se vea incluso los borrados con su marca
void __fastcall TForm1::Button7Click(TObject *Sender)
{
   RegAlumno reg; AnsiString linea,nombre;
   nombre=ruta+"listado-completo.csv";
   fstream f(nom.c_str(),ios::binary|ios::in);
   fstream t(nombre.c_str(),ios::out);
   if (!f.fail()) {
	   while (!f.eof()) {
		   f.read((char*)&reg,sizeof(reg));
		   if (!f.eof()) {
			   linea=AnsiString(reg.marca)+","+IntToStr(reg.cod)+","+reg.nom+","+reg.fecha.dia+","+reg.fecha.mes+","+reg.fecha.ano+","+reg.telefono;
			   byte n=linea.Length();
			   for (byte i=1; i<=n; i++) {
				   t.put(linea[i]);
			   }
			   t.put(10);
		   }
	   }
	   f.close(); t.close();
	   ShowMessage("listado completo generado");
   }
}
//---------------------------------------------------------------------------
//crear el archivo de indice por codigo
void __fastcall TForm1::Button8Click(TObject *Sender)
{
	RegAlumno reg; RegIdxCod regidx;
	fstream f(nom.c_str(),ios::binary|ios::in);
	fstream idx(nomCod.c_str(),ios::binary|ios::out);
	if (!f.fail()) {
		while (!f.eof()) {
			regidx.ref=f.tellg();
			f.read((char*)&reg,sizeof(reg));
			if (!f.eof()) {
			  if (reg.marca!='*') {
				regidx.cod=reg.cod;
				idx.write((char*)&regidx,sizeof(regidx));
			  }
			}
		}
		f.close();idx.close();
		ShowMessage("indice vcreado");
	}
}
//---------------------------------------------------------------------------
// busqueda de binaria de el archibo indice
long int TForm1::BusBinariaIdx(Word codB) {
	long int posi=-1,a,b,c;  RegIdxCod regi;  bool hallado;
	fstream fi(nomCod.c_str(),ios::binary|ios::in|ios::ate);
	if (!fi.fail()) {
		long int tamanoreg=fi.tellg();
		Cardinal totalreg=tamanoreg/sizeof(regi);
		a=0;
		b=totalreg-1;
		hallado=false;
		while ((a<=b)&&(!hallado))  {
			c=(a+b)/2;
			fi.seekg(c*sizeof(regi));
			fi.read((char*)&regi,sizeof(regi));
			if (codB==regi.cod) {
				posi=regi.ref;
				hallado=true;
			}  else if (codB<regi.cod)
					b=c-1;
			else
				a=c+1;
		}
		fi.close();
	}
	return posi;
}
//---------------------------------------------------------------------------


 //crear indice por nombre indexado
//---------------------------------------------------------------------------
void __fastcall TForm1::Button9Click(TObject *Sender)
{
	RegAlumno reg;
	RegIdxNom regi;
	fstream f(nom.c_str(),ios::binary|ios::in);
	fstream fi(nomNom.c_str(),ios::binary|ios::out);
	if (!f.fail()) {
		while (!f.eof()) {
		  regi.ref=f.tellg();
		  f.read((char*)&reg,sizeof(reg));
		  if (!f.eof()) {
			  if (reg.marca!='*') {
				 strcpy(regi.nom,reg.nom);
				 fi.write((char*)&regi,sizeof(regi));
			  }
		  }
		}
		f.close();
		fi.close();
		ShowMessage("archivo de indice por nombre creado");
	}
}
//---------------------------------------------------------------------------
 //listado de indice por codigo
void __fastcall TForm1::LISTADOS2Click(TObject *Sender)
{
	RegIdxCod reg; AnsiString linea,list;
	fstream f(nomCod.c_str(),ios::binary|ios::in);
	list=ruta+"ListadoPorCod.csv";
	fstream t(list.c_str(),ios::out);
	if (!f.fail()) {
		while (!f.eof()) {
			f.read((char*)&reg,sizeof(reg));
			if (!f.eof()) {
				linea=IntToStr(reg.cod)+","+reg.ref;
				byte n=linea.Length();
				for (byte i=1; i<=n; i++) {
				  t.put(linea[i]);
				}
				t.put(10);
			}
		}
		f.close(); t.close();
		ShowMessage("Listado de indice por codigo Generado");
	}
}
//---------------------------------------------------------------------------

//ordenamiento de selection short ,en el archibo de de indice x codigo
void __fastcall TForm1::ORDENAMINTO2Click(TObject *Sender)
{
   RegIdxCod ri,rm;
   Cardinal i,b,m;
   fstream fi(nomCod.c_str(),ios::binary|ios::in|ios::out|ios::ate);
   if (!fi.fail()) {
	 b=fi.tellg(); b=b-sizeof(rm);
	 while (b>0)
	 {
		m=0; fi.seekg(m);
		fi.read((char*)&rm,sizeof(rm));
		i=m+sizeof(rm);
		while (i<=b)
		 {
			fi.read((char*)&ri,sizeof(ri));
			if (ri.cod>rm.cod) {
				 m=i; rm=ri;
			}
			i=i+sizeof(ri);
		 }
		 if (b!=m) {
			  fi.seekg(b); fi.write((char*)&rm,sizeof(rm));
			  fi.seekg(m); fi.write((char*)&ri,sizeof(ri));
		 }
		 b=b-sizeof(rm);
	 }
	 fi.close();
	 ShowMessage("archivo indice x codigo ordenado");
   }
}
//---------------------------------------------------------------------------
//listado de indice por nombre y codigo
void __fastcall TForm1::listadodeindicepornombre1Click(TObject *Sender)
{
	RegIdxCod regi; RegAlumno reg;
	AnsiString linea,list;
	list=ruta+"listadoNom.csv";
	fstream t(list.c_str(),ios::out);
	fstream f(nom.c_str(),ios::binary|ios::in);
	fstream fi(nomCod.c_str(),ios::binary|ios::in);
	if (!f.fail()&&!fi.fail()) {
		while (!fi.eof())
		{
			fi.read((char*)&regi,sizeof(regi));
			if (!fi.eof()) {
				f.seekg(regi.ref);
				f.read((char*)&reg,sizeof(reg));
				linea=IntToStr(regi.cod)+","+reg.nom;
				byte n=linea.Length();
				for (byte i=1; i<=n; i++) {
					t.put(linea[i]);
				}
				t.put(10);
			}
		}
		f.close(); t.close(); fi.close();
		ShowMessage("listado por nombre crado");
	}
}
//---------------------------------------------------------------------------
// generrar un listado de maneta desendente
void __fastcall TForm1::listadodemanetadesensendente1Click(TObject *Sender)
{
  RegIdxCod regi; RegAlumno reg;
  Cardinal b;
  AnsiString list, linea;
  list=ruta+"listadoDes.txt";
  fstream t(list.c_str(),ios::out);
  fstream f(nom.c_str(),ios::binary|ios::in);
  fstream fi(nomCod.c_str(),ios::binary|ios::in|ios::ate);
  if (!f.fail()) {

	while (fi.tellg()>0) {
		fi.seekg(-sizeof(regi),ios::cur);
		fi.read((char*)&regi,sizeof(regi));
		fi.seekg(-sizeof(regi),ios::cur);
		f.seekg(regi.ref);
		f.read((char*)&reg,sizeof(reg));
		linea=IntToStr(reg.cod)+","+reg.nom+","+reg.telefono+","+reg.fecha.dia+","+reg.fecha.mes+","+reg.fecha.ano;
		for (byte i=1; i<=linea.Length(); i++) {
			t.put(linea[i]);
		}
		t.put(10);
    }
	fi.close(); t.close(); f.close();
	ShowMessage("listado Descendente generado");
  }
}
//---------------------------------------------------------------------------

// actualizar el reg de Alumnos de los nombres a la 1ra myuscula y lo demas en miniscula
char ConvertiToMayuscula(char x){
AnsiString min="abcdefghijklmnopqrstuvwxyzáéíóúüñ";
AnsiString may="ABCDEFGHIJKLMNOPQRSTUVWXYZÁÉÍÓÚÜÑ";
byte p=min.Pos(x);
	if (p>0) {
		x=may[p];
	}
return x;;
}
char ConvertiToMinuscula(char x){
AnsiString min="abcdefghijklmnopqrstuvwxyzáéíóúüñ";
AnsiString may="ABCDEFGHIJKLMNOPQRSTUVWXYZÁÉÍÓÚÜÑ";
byte p=may.Pos(x);
	if (p>0) {
		x=min[p];
	}
return x;
}
bool EsLetra(char x){
AnsiString let="ABCDEFGHIJKLMNOPQRSTUVWXYZÁÉÍÓÚÜÑabcdefghijklmnopqrstuvwxyzáéíóúüñ";
return let.Pos(x)>0;
}
AnsiString PrimeraPalMayus(AnsiString x) {
	byte n=x.Length();
	bool dentro=false;
	for (byte i=1; i<=n; i++) {
		if (EsLetra(x[i])) {
			if (dentro==false) {
				dentro=true;
				x[i]=ConvertiToMayuscula(x[i]);
			} else {
				x[i]=ConvertiToMinuscula(x[i]);
			}
		}  else {
			dentro=false;
		}
	}
	return x;
}
void __fastcall TForm1::actualizarlosnombreala1raMayuscula1Click(TObject *Sender)
{
  RegAlumno reg;
  fstream f(nom.c_str(),ios::binary|ios::in|ios::out);
  if (!f.fail()) {
	  while (!f.eof())
	  {   f.read((char*)&reg,sizeof(reg));
		  if (!f.eof()) {
			  if (reg.marca!='*') {
				AnsiString x=PrimeraPalMayus(reg.nom);
				strcpy(reg.nom,x.c_str());
				f.seekg(-sizeof(reg),ios::cur);
				f.write((char*)&reg,sizeof(reg));
				f.seekg(sizeof(reg),ios::cur);
				f.seekg(-sizeof(reg),ios::cur);
			  }
		  }
	  }
	  f.close();
	  ShowMessage("datos modificados");
  }
}
//---------------------------------------------------------------------------
//listado de los regitros que empieze en 50
byte ContDigit(Cardinal n) {
	byte cont=0;
	if (n==0)
		cont=1;
	else {
		while (n>0) {
		   cont++;
		   n=n/10;
		}
	}
	return cont;
}
bool Veri1NumInitConOtro(Cardinal Ngrande, byte Nbus) {
	byte digitG=ContDigit(Ngrande);
	byte digitB=ContDigit(Nbus);
	Cardinal divisor=pow(10,digitG-digitB);
	return (Ngrande/divisor)==Nbus;
}
void __fastcall TForm1::listadodelosregqueempizenen501Click(TObject *Sender)
{
   RegAlumno reg;
   AnsiString nombre,linea;
   nombre=ruta+"listado50.txt";
   fstream f(nom.c_str(),ios::binary|ios::in);
   fstream t(nombre.c_str(),ios::out);
   if (!f.fail()) {
	   while (!f.eof())
	   {
		   f.read((char*)&reg,sizeof(reg));
		   if (!f.eof()) {
			 if (reg.marca!='*') {
				 if (Veri1NumInitConOtro(reg.cod,50)) {
					   linea=IntToStr(reg.cod)+","+reg.nom;
					byte n=linea.Length();
					 for (byte i=1; i <=n; i++) {
						   t.put(linea[i]);
					 }
					t.put(10);
				 }
			 }
		   }
	   }
	   f.close(); t.close();
	   ShowMessage("listado creado");
   }
}
//---------------------------------------------------------------------------
// aumentar un dia a los registros Alumnos

void __fastcall TForm1::aumentar1diaalosreg1Click(TObject *Sender)
{
	RegAlumno reg;
	fstream f(nom.c_str(),ios::binary|ios::in|ios::out);
	if (!f.fail()) {
		while (!f.eof())
		{
			f.read((char*)&reg,sizeof(reg));
			if (!f.eof()) {
				if (reg.marca!='*') {
				   f.seekg(-sizeof(reg),ios::cur);
				   if (reg.fecha.dia<31) {
					   reg.fecha.dia=reg.fecha.dia+1;
				   } else {
					   if (reg.fecha.mes<12) {
						   reg.fecha.mes=reg.fecha.mes+1;
						   reg.fecha.dia=1;
					   } else {
						   reg.fecha.ano=reg.fecha.ano+1;
						   reg.fecha.dia=1;
						   reg.fecha.mes=1;
					   }
				   }
				   f.write((char*)&reg,sizeof(reg));
				   f.seekg(sizeof(reg), ios::cur);
				   f.seekg(-sizeof(reg), ios::cur);
				}
			}
		}
		f.close(); ShowMessage("se aumento un dia ");
	}
}
//---------------------------------------------------------------------------
//hacer un proceso para reconstruir un registro a partir de un listado
//pregunta 2
void __fastcall TForm1::Button11Click(TObject *Sender)
{
	RegAlumno reg;
	AnsiString list = ruta + "Listado.csv";
	fstream t(list.c_str(), ios::binary | ios::in);
	fstream f(nom.c_str(), ios::binary | ios::out);

	if (!t.fail() && !f.fail()) {
		AnsiString aux="";
		char c;
		byte nroCampo = 1;

		while (!t.eof()) {
			t.read((char*)&c, sizeof(c));

			if (!t.eof()) {
				if (c == ',' || c == 10) {

					if (nroCampo == 1) {
						reg.cod = StrToInt(aux);
					}
					else if (nroCampo == 2) {
						strcpy(reg.nom, aux.c_str());
					}
					else if (nroCampo == 3) {
						reg.fecha.dia = StrToInt(aux);
					}
					else if (nroCampo == 4) {
						reg.fecha.mes = StrToInt(aux);
					}
					else if (nroCampo == 5) {
						reg.fecha.ano = StrToInt(aux);
					}
					else if (nroCampo == 6) {
						reg.telefono = StrToInt(aux);
					}
					aux = "";

					if (c == ',') {
						nroCampo++;
					}
					else if (c == 10) {
						reg.marca = ' ';
						f.write((char*)&reg, sizeof(reg));
						nroCampo = 1;
					}
				}
				else if (c != 13) {
					aux = aux + c;
				}
			}
		}
		f.close();
		t.close();

		ShowMessage("registro de con listado");
	}
}
//---------------------------------------------------------------------------
//pregunta 3

void __fastcall TForm1::N111Click(TObject *Sender)
{
	RegIdxCod regi, regiSiguiente;
	RegAlumno reg;

	fstream fi(nomCod.c_str(), ios::binary | ios::in | ios::ate);
	fstream f(nom.c_str(), ios::binary | ios::in | ios::out);

	if (!fi.fail() && !f.fail()) {
		long int tamanoIdx = fi.tellg();
		int totalReg = tamanoIdx / sizeof(regi);
		if (totalReg > 0) {
			for (int i = 0; i < totalReg; i++) {
				fi.seekg(i * sizeof(regi));
				fi.read((char*)&regi, sizeof(regi));
				Word codSiguiente;
				if (i < totalReg - 1) {
					fi.read((char*)&regiSiguiente, sizeof(regiSiguiente));
					codSiguiente = regiSiguiente.cod;
				} else {
					fi.seekg(0);
					fi.read((char*)&regiSiguiente, sizeof(regiSiguiente));
					codSiguiente = regiSiguiente.cod;
				}

				f.seekg(regi.ref);
				f.read((char*)&reg, sizeof(reg));
				reg.telefono = codSiguiente;
				AnsiString nombreFinal = PrimeraPalMayus(reg.nom);
				strcpy(reg.nom, nombreFinal.c_str());
				f.seekg(regi.ref);
				f.write((char*)&reg, sizeof(reg));
				f.seekg(sizeof(reg), ios::cur);
				f.seekg(-sizeof(reg), ios::cur);
			}
			ShowMessage("Archivo modificado");
		}
		fi.close();
		f.close();
	}
}
//---------------------------------------------------------------------------



