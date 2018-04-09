#include <iostream>
#include <string>
#include <array>
#include <fstream> // pour les fichiers


/********************************************************************************/
/* recherche naive								*/
/********************************************************************************/

int recherche_naive_g(int noligne, std::string ligne, std::string motif) {
// on recherche toutes les occurrences de 'motif' dans 'texte'
// retourne le nombre de comparaisons
	int out=0;
	int L = ligne.size(), M = motif.size();
	for(int i=0;i<=L-M;i++){
		/*for(int j=0;j<M;j++) {
			out++;
			if(motif[j]!=ligne[i+j]) break;
			if(j==M-1) std::cout << "Motif trouve\' en:"<<i<<std::endl;
		}*/
		int j=0;
		while (motif[j]==ligne[i+j]){
			out++;
			if(j==M-1) std::cout << "Motif trouve\' en:"<<i<<std::endl;
			j++;
		}
		if(motif[j]!=ligne[i+j])out++;
	}
	return out;
}

int recherche_naive_d(int noligne, std::string ligne, std::string motif) {
// on recherche toutes les occurrences de 'motif' dans 'texte'
// retourne le nombre de comparaisons
	int out=0;
	int L = ligne.size(), M = motif.size();
	for(int i=0;i<=L-M;i++){
		int j=M-1;
		while (motif[j]==ligne[i+j]){
			out++;
			j--;
			if(j==0) std::cout << "Motif trouve\' en:"<<i<<std::endl;
		}
		if(motif[j]!=ligne[i+j])out++;
	}
	return out;
}

long recherche_naive_fichier(std::string nom_fich, std::string motif){
// recherche toutes les occurrences de 'motif' dans le fichier texte 'nom_fich'
// retourne le nombre de comparaisons effectuées, ou -1 si erreur

std::ifstream f;
std::string texte;
long nb_comp = 0; // nombre de comparaisons de caractères effectuées
int noligne = 1; // numero de ligne

	f.open(nom_fich, std::ios::in); // ouverture du fichier en lecture
	if (!f)
	{
		std::cout << "impossible d'ouvrir le fichier\n";
		return(-1);
	}

	// recherche en examinant le motif à partir de la gauche
	while (std::getline(f,texte))// lecture de la ligne entière, retourne false si erreur
	{
		nb_comp += recherche_naive_g(noligne,texte,motif);
		nb_comp += recherche_naive_d(noligne,texte,motif);
		noligne++;
	}

	f.close();
	return nb_comp;
}


int main(int argc, char **argv)
{
	if ( argc < 2 )
	{
		std::cout << "Usage: "<< argv[0] << " NOM_DU_FICHIER\n";
		return (EXIT_FAILURE);
	}

	std::string nom_fich = argv[1]; // le nom du fichier contenant le texte
	std::string motif; // le motif
	long nb_comp; // nombre de comparaisons


	std::cout << "Motif ? ";
	std::getline(std::cin, motif); 
	nb_comp = recherche_naive_fichier(nom_fich, motif);
	if (nb_comp >= 0 )
		std::cout << "nombre de comparaisons (g/d + d/g): " << nb_comp << std::endl;

	return EXIT_SUCCESS;
}