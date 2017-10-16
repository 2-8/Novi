#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cctype>
using namespace std;

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

typedef struct Tcvor
{
	int x;
	struct Tcvor *sled;
};

typedef Tcvor *Pcvor;

void Ispis(Pcvor glava)
{
	int i=1;
	while(glava)
	{
		printf("\n Clan %d : %d",i,glava->x);
		i++;
		glava=glava->sled;
	}
	cout<<endl;
}

void Formiranje(Pcvor *glava)
{

	Pcvor novi;
	int x;
	cout<<"Unesi"<<endl;
	while(scanf("%d",&x)==1)
	{
		novi=new Tcvor;
		novi->x=x;
		novi->sled=*glava;
		*glava=novi;
	}
}

void FormDno(Pcvor *glava)
{
	Pcvor tek,pret,novi;
	int x;
	cout<<"Unesi"<<endl;
	while(scanf("%d",&x)==1)
	{
		novi=new Tcvor;
		novi->x=x;
		novi->sled=NULL;
			if(*glava)
		{
			tek=*glava;
			while(tek)
			{
				pret=tek;
				tek=tek->sled;
			}
			pret->sled=novi;
		}
			else
				*glava=novi;
	}

}

int Suma(Pcvor glava)
{
	Tcvor *pom;
	int s=0;
	for(pom=glava;pom!=NULL;pom=pom->sled)
		s+=pom->x;
	return s;
}

int brEL(Pcvor glava)
{
	Tcvor *pom;
	int br=0;
	for(pom=glava;pom!=NULL;pom=pom->sled)
		br++;
	return br;
}

int Sadrzi(Pcvor gl1, Pcvor *gl2)
{
	Pcvor tek=*gl2;
	while(1)
	{
		while(gl1 && gl1->x != tek->x)
		{
			gl1=gl1->sled;
		}
		if(gl1 == NULL)
			return 0;
		while(tek && gl1 && gl1->x == tek->x)
		{
			gl1=gl1->sled;
			tek=tek->sled;
		}
		if(tek == NULL)
		{
			return 1;
		}
		else
			tek=*gl2;
	}
}

void Nadovezivanje(Pcvor gl1, Pcvor *gl2)
{
	Pcvor novi;
	Tcvor *pom;
	for(pom=gl1;pom!=NULL;pom=pom->sled)
	{
		novi=new Tcvor;
		novi->x=pom->x;
		novi->sled=*gl2;
		*gl2=novi;
	}
}

void Brisi(Pcvor *glava)
{
	Pcvor tek=*glava;
	while(*glava)
	{
		tek=*glava;
		*glava=(*glava)->sled;
		tek->sled=NULL;
		free(tek);
	}
}

void main()
{
	Pcvor glava;
	glava = NULL;
	Formiranje(&glava);
	Ispis(glava);
	int suma = Suma(glava);
	int brEl = brEL(glava);
	cout<<endl<<"Zbir svih clanova: "<<suma<<endl;
	cout<<"Broj elemenata: "<<brEl<<endl;
	getchar();

	Pcvor pomGl;
	pomGl=NULL;
	FormDno(&pomGl);
	Ispis(pomGl);
	int s2=Suma(pomGl);
	int brEl2=brEL(pomGl);
	cout<<endl<<"Zbir svih clanova: "<<s2<<endl;
	cout<<"Broj elemenata: "<<brEl2<<endl;

	if(brEl>brEl2)
	{
		int sad;
		sad=Sadrzi(glava, &pomGl);
		if(sad==1)
		{
			cout<<"Sadrzi!"<<endl;
		}
		else
		{
			cout<<"Ne sadrzi"<<endl;
			Nadovezivanje(pomGl,&glava);
			cout<<"Liste su spojene"<<endl;
			Ispis(glava);
		}
	}
	else if(brEl<brEl2)
	{
		int sad;
		sad=Sadrzi(pomGl, &glava);
		if(sad==1)
		{
			cout<<"Sadrzi!"<<endl;
		}
		else
		{
			cout<<"Ne sadrzi!"<<endl;
			Nadovezivanje(glava,&pomGl);
			cout<<"Liste su spojene"<<endl;
			Ispis(pomGl);
		}
	}
	else
	{
		int sad;
		sad=Sadrzi(glava, &pomGl);
		if(sad==1)
			cout<<"Sadrzi!"<<endl;
		else
		{
			cout<<"Ne sadrzi!"<<endl;
			if(suma>s2)
			{
				Nadovezivanje(glava,&pomGl);
				cout<<"Liste su spojene"<<endl;
				Ispis(pomGl);
			}
			else if(suma<s2)
			{
				Nadovezivanje(pomGl,&glava);
				cout<<"Liste su spojene"<<endl;
				Ispis(glava);
			}
			else
			{
				cout<<"Sume su iste, nema nadovezivanja"<<endl;
			}
		}
	}

	Brisi(&glava);
	Brisi(&pomGl);
	cout<<"Liste su oslobodjene"<<endl;
	system("pause");
}