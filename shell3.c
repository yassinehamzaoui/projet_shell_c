#include "appel_system.h"

#define sim_table_size 1024

char * sim_lire_ligne()
{
   int tablesize = sim_table_size ;
   int position = 0;
   char *table = malloc(sizeof(char) * tablesize );
   int c;
   
   while (1) {
    c = getchar();

    if (c == EOF) {
      exit(EXIT_SUCCESS);
    } else if (c == '\n') {
      table[position] = '\0';
      return table;
    } else {
      table[position] = c;
    }
    position++;
	if (position >= tablesize) {
      tablesize += sim_table_size ;
      table = realloc(table, tablesize);
      }
	}
   return table;
}

#define sim_tok_delim " "
#define sim_tok_bufsize 64

char** sim_split_line(char* line)
{
	int position = 0;
	char* token;
	char **tokens = malloc(sim_table_size * sizeof(char*));
	token = strtok (line," ");
    while (token != NULL)
    {
		tokens[position] = token;
		token = strtok (NULL, " ");
		position++;
	}
	tokens[position] = NULL;
return tokens;
}

int sim_execute(char **args)
{
	int i=0;
	int k;
	// cas d'une entrée vide
	if (args[0] == NULL) 
		{
			printf("Entrez une commande [erreur 0] \n");
			return 1;
		}
	// afficher : afficher normal
	if((strcmp(args[0],"afficher") == 0) && (args[1] == NULL))
		{
			k = fonction_afficher();
			return k;
		}
	// afficher -d : afficher details
	else if((strcmp(args[0],"afficher") == 0) && (strcmp(args[1],"-d") == 0) && (args[2] == NULL))
		{
			k = fonction_afficher_details();
			return k;
		}
	// quitter -c : confirmer la sortie du shell
	else if (strcmp(args[0],"quitter") == 0)
		{
			k = fonction_quitter();
			return 0;
		}
	// effacer : permet d'effacer l'ecran 
	else if (strcmp(args[0],"effacer")==0)
	{
			k =  fonction_clear();
			return k;
	}
	// acceder "chemin" : executer cd pour acceder au chemin ou au dossier
	else if((strcmp(args[0],"acceder") == 0))
		{
			if(args[1] == NULL)
				{
					printf("Argument incomplet [erreur 1] \n");
					return 1;
				}
			k = fonction_acceder(args);
			return 1;
		}
	// lister "nom fichier " : liste le contenu d'un fichier
	else if (strcmp(args[0],"lister")==0 && (args[2] == NULL))
	{
			if(args[1] == NULL)
				{
					printf("Argument incomplet [erreur 1] \n");
					return 1;
				}
			k =  fonction_lister(args);
			return k;
	}
	// supprimer "nom fichier ou dossier " : supprime un fichier ou un dossier
	else if (strcmp(args[0],"supprimer")==0)
	{
			if(args[1] == NULL)
				{
					printf("Argument incomplet [erreur 1] \n");
					return 1;
				}
			k = fonction_supprimer(args);
			return 1;
	}
	// chemin : afficher le chemin courant 
	else if (strcmp(args[0],"chemin")==0 && (args[1] == NULL))
	{
			k = fonction_chemin();
			return 1;
	}
	// editer "nomfichier" : ouvre l'éditeur vi
	else if (strcmp(args[0],"editer")==0 && (args[1] != NULL))
	{
			k = fonction_editer(args);
			return 1;
	}
	// creer -f "nomfichier" : création fichier
	else if ((strcmp(args[0],"creer")==0) && (strcmp(args[1],"-f") == 0))
	{
			if((args[1] == NULL)||(args[2] == NULL))
				{
					printf("Argument incomplet [erreur 1] \n");
					return 1;
				}
			k = fonction_creer_fichier(args);
			return 1;
	}
	// creer -d "nomdossier" : création dossier	
	else if ((strcmp(args[0],"creer")==0) && (strcmp(args[1],"-d") == 0))
	{
			if((args[1] == NULL)||(args[2] == NULL))
				{
					printf("Argument incomplet [erreur 1] \n");
					return 1;
				}
			k = fonction_creer_dossier(args);
			return 1;
	}
	// processus : permet d'afficher tous les processus courant
	// processus "utilisateur" : permet d'afficher les processus courant d'un utilisateur spécifique
	else if ((strcmp(args[0],"processus")==0) && (args[2] == NULL))
	{
			if((args[1] == NULL))
				{
					k = fonction_processus(args);
					return 1;
				}
			k = fonction_processus_user(args);
			return 1;
	}
	// @ : redirection
	// afficher @ "nomfichier" : redirection de la commande afficher vers un fichier
	else if ((strcmp(args[0],"afficher")==0) && (strcmp(args[1],"@") == 0))
	{
			if((args[2] == NULL))
				{
					printf("Argument incomplet [erreur 1] \n");
					return 1;
				}
			k = fonction_redirection_afficher(args);
			return 1;
	}
	// afficher -d @ "nomfichier" : redirection de la commande afficher -d vers un fichier
	else if ((strcmp(args[0],"afficher")==0) && (strcmp(args[1],"-d") == 0) && (strcmp(args[2],"@") == 0))
	{
			if((args[2] == NULL))
				{
					printf("Argument incomplet [erreur 1] \n");
					return 1;
				}
			k = fonction_redirection_afficher_d(args);
			return 1;
	}		
	// chemin @ "nomfichier" : redirection de la commande chemin vers un fichier
	else if ((strcmp(args[0],"chemin")==0) && (strcmp(args[1],"@") == 0))
	{
			if((args[2] == NULL))
				{
					printf("Argument incomplet [erreur 1] \n");
					return 1;
				}
			k = fonction_redirection_chemin(args);
			return 1;
	}
	// processus @ "nomfichier" : redirection de la commande processus vers un fichier
	else if ((strcmp(args[0],"processus")==0) && (strcmp(args[1],"@") == 0))
	{
			if((args[2] == NULL))
				{
					printf("Argument incomplet [erreur 1] \n");
					return 1;
				}
			k = fonction_redirection_processus(args);
			return 1;
	}
	// processus "utilisateur" @ "nomfichier" : redirection de la commande processus "utilisateur" vers un fichier
	else if ((strcmp(args[0],"processus")==0) && (args[1] != NULL) && (strcmp(args[2],"@") == 0))
	{
			if((args[3] == NULL))
				{
					printf("Argument incomplet [erreur 1] \n");
					return 1;
				}
			k = fonction_redirection_processus_user(args);
			return 1;
	}	
	// deplacer "chemin1" "chemin2" : permet de deplacer un fichier d'un chemin vers un autre
	else if ((strcmp(args[0],"deplacer")==0))
	{
			if((args[2] == NULL) || (args[1] == NULL))
				{
					printf("Argument incomplet [erreur 1] \n");
					return 1;
				}
			k = fonction_deplacer(args);
			return 1;
	}
	// copier "chemin1" "chemin2" : permet de copier un fichier d'un chemin vers un autre
	else if ((strcmp(args[0],"copier")==0))
	{
			if((args[2] == NULL) || (args[1] == NULL))
				{
					printf("Argument incomplet [erreur 1] \n");
					return 1;
				}
			k = fonction_copier(args);
			return 1;
	}
	// droit "privilèges" "nomfichier" : permet d'affecter des privilèges d'un utilisateur spécifique
	else if ((strcmp(args[0],"droit")==0))
	{
			if((args[1] == NULL) || (args[2] == NULL))
				{
					printf("Argument incomplet [erreur 1] \n");
					return 1;
				}
			k = fonction_droit(args);
			return 1;
	}
	// afficher # chercher "nom/caractère" : permet de chercher un mot
	else if((strcmp(args[0],"afficher")==0) && (strcmp(args[1],"#")==0))
	{
			if((args[1] == NULL) || (args[2] == NULL) || (args[3] == NULL))
				{
					printf("Argument incomplet [erreur 1] \n");
					return 1;
				}
			// afficher # chercher "nom/caractère" : permet de chercher un mot contenant les caractères spécifiés
			if ((strcmp(args[0],"afficher")==0) && (strcmp(args[2],"chercher")==0))
				{
					k = fonction_pipe_chercher(args);
				}
			// afficher # compter ligne : permet de ccompter le nombre de ligne
			if ((strcmp(args[0],"afficher")==0) && (strcmp(args[2],"compter")==0) && (strcmp(args[3],"ligne")==0))
				{
					k = fonction_pipe_compter_ligne(args);
				}
			return 1;
	}
	else if ((strcmp(args[0],"file_message")==0))
	{
			if((args[1] == NULL))
				{
					printf("Argument incomplet [erreur 1] \n");
					return 1;
				}
			//file_message -s -c 10 -t 5 -m "message"
			if((strcmp(args[1],"-s") == 0) && (strcmp(args[2],"-c") == 0) && (strcmp(args[4],"-t") == 0) && (strcmp(args[6],"-m") == 0))
				{
					k = fonction_file_de_message1(args);
					return 1;
				}
			//file_message -r -c 10 -t 5
			if((strcmp(args[1],"-r") == 0) && (strcmp(args[2],"-c") == 0) && (strcmp(args[4],"-t") == 0))
				{
					k = fonction_file_de_message2(args);
					return 1;
				}				
			return 1;
	}
	//compiler "nomprog.c" -o "nomexecutable"
	else if ((strcmp(args[0],"compiler")==0) && (strcmp(args[2],"-e") == 0))
	{
			if((args[1] == NULL) || (args[2] == NULL) || (args[3] == NULL))
				{
					printf("Argument incomplet [erreur 1] \n");
					return 1;
				}
			k = fonction_compiler(args);
			return 1;
	}
	//help
	else if ((strcmp(args[0],"help")==0))
		{
			k = fonction_help();
			return 1;
		}
	// cas d'une commande non disponible
	else
		{ 
			printf("Entrez une commande valide [erreur 1] \n");
			return 1;
		}
}

void sim_boucler(void)
{
  char *line;
  char **args;
  int status = 1;
  char *buffer;
  do {
	if(fork()==0)
	{
	printf("Shell_Sim >> ");
	fonction_path();
	}
    line = sim_lire_ligne();
    args = sim_split_line(line);
    status = sim_execute(args);

    free(args);
	free(line);
	
  } while (status==1);
}

int main(int argc, char **argv)
{
  sim_boucler();  
  return EXIT_SUCCESS;
}
