#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <time.h>


int fonction_afficher(void )
{
	system("ls");
	return 1;
}

int fonction_afficher_details(void )
{
	system("ls -l");
	return 1;
}
	
int fonction_clear(void )
{
	system("clear");
	return 1;
}	

int fonction_quitter(void )
{
	system("exit");
	return 0;
}

int fonction_acceder(char** args){
	char * path;
	path = args[1];
	chdir(path);
	return 1;
}
unsigned char buffer[256]; 
void fonction_path(void )
{
	char * path;
	int p[2],i=0;
	
	char c;
	if(pipe(p)==-1)
	{
		perror("Problème pipe [Erreur 3]");
		exit (1);
	}
	if(fork()==0)
	{
		dup2(p[1],1);
		close(p[0]);
		close(p[1]); 
		execlp("pwd","pwd",NULL);
		perror("Problème Execlp [Erreur 4]");
	}
	wait(0);
	close(p[1]);
	dup2(p[0],0);
	while(read(p[0],&c,1)!=0)
	{
		buffer[i] = c;
		i++;
	}
	buffer[i-1]=0;
	printf("%s : ",buffer); 
}
int fonction_lister(char ** args)
{
	int i, p[2];
	char c, res[4096];
	char * path;
	if(pipe(p)==-1)
	{
		perror("Problème pipe [Erreur 3]");
		exit (1);
	}
	if(fork()==0)
	{
		dup2(p[1],1);
		close(p[0]);
		close(p[1]);
		path = args[1];
		execlp("cat","cat",path,NULL);
		perror("Problème Execlp [Erreur 4]");
		exit(1);
	}
	wait(0);
	close(p[1]);
	i=0;
	while(read(p[0],&c,1)!=0)
	{
		res[i++]=c;
	}
	res[i-1]=0;
	printf("%s\n",res);
	close(p[0]);
	close(p[1]);
	return 1;
}

int fonction_supprimer(char **args)
{

	int p[2];
	if(pipe(p)==-1)
	{
		perror("Problème pipe [Erreur 3]");
		exit (1);
	}

	if(fork()==0)
	{
		dup2(p[1],1);
		close(p[0]);
		close(p[1]);
		execlp("rm","rm","-r",args[1],NULL);
		perror("Problème Execlp [Erreur 4]");
		exit(1);
	}

	close(p[1]);
	return 1;

}

int fonction_chemin(void )
{
	system("pwd");
	return 1;	
}
int fonction_creer_fichier(char ** args )
{
	int p[2];
	if(pipe(p)==-1)
	{
		perror("Problème pipe [Erreur 3]");
		exit (1);
	}
	if(fork()==0)
	{
		dup2(p[1],1);
		close(p[0]);
		close(p[1]);
		execlp("touch","touch",args[2],NULL);
		perror("Problème Execlp [Erreur 4]");
		exit(1);
	}

	close(p[1]);
	return 1;
}
int fonction_creer_dossier(char ** args)
{
	int p[2];
	if(pipe(p)==-1)
	{
		perror("Problème pipe [Erreur 3]");
		exit (1);
	}

	if(fork()==0)
	{
		dup2(p[1],1);
		close(p[0]);
		close(p[1]);
		execlp("mkdir","mkdir",args[2],NULL);
		perror("Problème Execlp [Erreur 4]");
		exit(1);
	}

	close(p[1]);
	return 1;
}

// Début des fonctions de redirections

int fonction_redirection_afficher(char ** args)
{
	int d, p[2];
	if(pipe(p)==-1)
	{
		perror("Problème pipe [Erreur 3]");
		exit (1);
	}
	if(fork()==0)
	{
		d = open(args[2],O_WRONLY | O_TRUNC | O_CREAT, 0666);
		dup2(d,1);
		close(d);
		execlp("ls","ls",NULL);
		perror("Problème Execlp [Erreur 4]");
		exit(1);
	}

	return 1;
}

int fonction_redirection_afficher_d(char ** args)
{
	int d, p[2];
	if(pipe(p)==-1)
	{
		perror("Problème pipe [Erreur 3]");
		exit (1);
	}
	if(fork()==0)
	{
		d = open(args[3],O_WRONLY | O_TRUNC | O_CREAT, 0666);
		dup2(d,1);
		close(d);
		execlp("ls","ls","-l",NULL);
		perror("Problème Execlp [Erreur 4]");
		exit(1);
	}

	return 1;
}

int fonction_redirection_chemin(char ** args)
{
	int d, p[2];
	if(pipe(p)==-1)
	{
		perror("Problème pipe [Erreur 3]");
		exit (1);
	}
	if(fork()==0)
	{
		d = open(args[2],O_WRONLY | O_TRUNC | O_CREAT, 0666);
		dup2(d,1);
		close(d);
		execlp("pwd","pwd",NULL);
		perror("Problème Execlp [Erreur 4]");
		exit(1);
	}

	return 1;
}
int fonction_redirection_processus(char ** args)
{
	int d, p[2];
	if(pipe(p)==-1)
	{
		perror("Problème pipe [Erreur 3]");
		exit (1);
	}
	if(fork()==0)
	{
		d = open(args[2],O_WRONLY | O_TRUNC | O_CREAT, 0666);
		dup2(d,1);
		close(d);
		execlp("ps","ps",NULL);
		perror("Problème Execlp [Erreur 4]");
		exit(1);
	}

	return 1;
}

int fonction_redirection_processus_user(char ** args)
{
	int d, p[2];
	if(pipe(p)==-1)
	{
		perror("Problème pipe [Erreur 3]");
		exit (1);
	}
	if(fork()==0)
	{
		d = open(args[3],O_WRONLY | O_TRUNC | O_CREAT, 0666);
		dup2(d,1);
		close(d);
		execlp("ps","ps","-u",args[1],NULL);
		perror("Problème Execlp [Erreur 4]");
		exit(1);
	}

	return 1;
}



// Fin des fonctions de redirections


int fonction_copier(char ** args)
{
	int p[2];
	if(pipe(p)==-1)
	{
		perror("Problème pipe [Erreur 3]");
		exit(1);
	}

	if(fork()==0)
	{
		dup2(p[1],1);
		close(p[0]);
		close(p[1]);
		execlp("cp","cp",args[1],args[2],NULL);
		perror("Problème Execlp [Erreur 4]");
		exit(1);
	}
	return 1;
}
int fonction_deplacer(char ** args)
{

	int p[2];
	if(pipe(p)==-1)
	{
		perror("Problème pipe [Erreur 3]");
		exit(1);
	}

	if(fork()==0)
	{
		dup2(p[1],1);
		close(p[0]);
		close(p[1]);
		execlp("mv","mv",args[1],args[2],NULL);
		perror("Problème Execlp [Erreur 4]");
		exit(1);
	}
	return 1;
}

int fonction_processus(char ** args)
{
	char c, res[4096];	
	int i=0,p[2];
	if(pipe(p)==-1)
	{
		perror("Problème pipe [Erreur 3]");
		exit(1);
	}

	if(fork()==0)
	{
		dup2(p[1],1);
		close(p[0]);
		close(p[1]);
		execlp("ps","ps",NULL);
		perror("Problème Execlp [Erreur 4]");
		exit(1);
	}
	wait(0);
	close(p[1]);
	i=0;
	while(read(p[0],&c,1)!=0)
	{
		res[i++]=c;
	}
	res[i-1]=0;
	printf("%s\n",res);
	close(p[0]);
	close(p[1]);
	return 1;
}
int fonction_processus_user(char ** args)
{
	char c, res[8192];
	int i=0,p[2];
	if(pipe(p)==-1)
	{
		perror("Problème pipe [Erreur 3]");
		exit(1);
	}

	if(fork()==0)
	{
		dup2(p[1],1);
		close(p[0]);
		close(p[1]);
		execlp("ps","ps","-u",args[1],NULL);
		perror("Problème Execlp [Erreur 4]");
		exit(1);
	}
	wait(0);
	close(p[1]);
	while(read(p[0],&c,1)!=0)
	{
		res[i++]=c;
	}
	res[i-1]=0;
	printf("%s\n",res);
	close(p[0]);
	close(p[1]);
	return 1;
}

int fonction_droit(char ** args)
{
	int p[2];
	char c, res[50];
	if(pipe(p)==-1)
	{
		perror("Problème pipe [Erreur 3]");
		exit(1);
	}
	if(fork()==0)
	{
		dup2(p[1],1);
		close(p[0]);
		close(p[1]);
		execlp("chmod","chmod",args[1],args[2],NULL);
		perror("Problème Execlp [Erreur 4]");
		exit(1);
	}

return 1;
}
int fonction_editer(char **args)
{
	execlp("nano","nano",args[1],NULL);
	perror("Problème Execlp [Erreur 4]");
	exit(1);
return 1;
}

int fonction_pipe_chercher(char **args)
{
	int p[2],k[2],i;
	char c, res[100];
	if(pipe(p)==-1)
	{
		perror("Problème pipe [Erreur 3]");
		exit(1);
	}
	if(pipe(k)==-1)
	{
		perror("Problème pipe [Erreur 3]");
		exit(1);
	}
	if(fork()==0)
	{
		dup2(p[1],1);
		close(p[1]);
		close(p[0]);
		execlp("ls","ls",NULL);
		perror("erreur cmd 1");
		exit(1);
	}
	if(fork()==0)
	{
		dup2(p[0],0);
		dup2(k[1],1);
		close(p[1]);
		close(k[1]);
		execlp("grep","grep",args[3],NULL);
		perror("erreur cmd 2");
		exit(1);
	}
	close(k[1]);
	close(p[1]);
	while(read(k[0],&c,1)!=0)
	{
		res[i++]=c;
	}
	res[i-1]=0;
	printf("%s\n",res);
	
	return 1;
}

int fonction_pipe_compter_ligne(char **args)
{
	int p[2],k[2],i;
	char c, res[50];
	if(pipe(p)==-1)
	{
		perror("Problème pipe [Erreur 3]");
		exit(1);
	}
	if(pipe(k)==-1)
	{
		perror("Problème pipe [Erreur 3]");
		exit(1);
	}
	if(fork()==0)
	{
		dup2(p[1],1);
		close(p[1]);
		close(p[0]);
		execlp("ls","ls",NULL);
		perror("erreur cmd 1");
		exit(1);
	}
	if(fork()==0)
	{
		dup2(p[0],0);
		dup2(k[1],1);
		close(p[1]);
		close(k[1]);
		execlp("wc","wc","-l",NULL);
		perror("erreur cmd 2");
		exit(1);
	}
	close(k[1]);
	close(p[1]);
	while(read(k[0],&c,1)!=0)
	{
		res[i++]=c;
	}
	res[i-1]=0;
	printf("%s\n",res);
	
	return 1;
}

int fonction_file_de_message1(char **args)
{
	int numfms = -1;
	int ch,cle,n,mtype;
	typedef struct
	{
		int mtype;
		char mtext[256];
	}MESSAGE;

	MESSAGE message;

	#define LGMES sizeof(message.mtext)

	cle = (int)args[3];

	numfms=msgget(cle,IPC_CREAT | 0666);

	if(numfms==-1)
	{
		perror("case 1 erreur msgget");
		exit(1);
	}
	char str[80];
	int i=8;
	message.mtype = (int)args[5];
	strcpy (str,args[7]);
	while(args[i]!=NULL)
	{
		strcat (str," ");
		strcat (str,args[i]);
		i++;		
	}
	sprintf(message.mtext,"%s",str);
	if(msgsnd(numfms,&message,LGMES,IPC_NOWAIT)==-1)
	{
		perror("erreur msgsnd");
	}

return 1;
}

int fonction_file_de_message2(char **args)
{
	int numfms = -1;
	int ch,cle,n,mtype;
	typedef struct
	{
		int mtype;
		char mtext[256];
	}MESSAGE;

	MESSAGE message;

	#define LGMES sizeof(message.mtext)

	cle = (int)args[3];
	
	numfms=msgget(cle,IPC_CREAT | 0666);

	if(numfms==-1)
	{
		perror("case 1 erreur msgget");
		exit(1);
	}
	message.mtype = (int)args[5];
	
	n=msgrcv(numfms,&message,LGMES,mtype,IPC_NOWAIT); /* type determine */
	if(n==-1)
	{
		perror("case 5 erreur msgrcv");
		exit(1);
	}
	else
	{
		printf("Recu message : **%s**\n",message.mtext);	
	}
	
return 1;
}


int fonction_compiler(char **args)
{
	if(fork()==0)
	{
	execlp("gcc","gcc",args[1],"-o",args[3],NULL);
	}

	return 1;
}

int fonction_help()
{
	
printf("Fonctionnalités :"
	"\n -> afficher : afficher normal"
	"\n -> afficher -d : afficher details"
	"\n -> quitter -c : confirmer la sortie du shell"
	"\n -> effacer : permet d\'effacer l\'ecran"
	"\n -> acceder \"chemin\" : executer cd pour acceder au chemin ou au dossier"
	"\n -> lister \"nom fichier\" : liste le contenu d'un fichier"
	"\n -> supprimer \"nom fichier ou dossier\" : supprime un fichier ou un dossier"
	"\n -> chemin : afficher le chemin courant"
	"\n -> editer \"nomfichier\" : ouvre l'éditeur vi"
	"\n -> creer -f \"nomfichier\" : création fichier"
	"\n -> creer -d \"nomdossier\" : création dossier"	
	"\n -> processus : permet d'afficher tous les processus courant"
	"\n -> processus \"utilisateur\" : permet d'afficher les processus courant d'un utilisateur spécifique"
	"\n -> @ : redirection"
	"\n -> afficher @ \"nomfichier\" : redirection de la commande afficher vers un fichier"
	"\n -> afficher -d @ \"nomfichier\" : redirection de la commande afficher -d vers un fichier"
	"\n -> chemin @ \"nomfichier\" : redirection de la commande chemin vers un fichier"
	"\n -> processus @ \"nomfichier\" : redirection de la commande processus vers un fichier"
	"\n -> processus \"utilisateur\" @ \"nomfichier\" : redirection de la commande processus \"utilisateur\" vers un fichier"
	"\n -> deplacer \"chemin1\" \"chemin2\" : permet de deplacer un fichier d'un chemin vers un autre"
	"\n -> copier \"chemin1\" \"chemin2\" : permet de copier un fichier d'un chemin vers un autre"
	"\n -> droit \"privilèges\" \"nomfichier\" : permet d'affecter des privilèges d'un utilisateur spécifique"
	"\n -> afficher # chercher \"nom/caractère\" : permet de chercher un mot"
	"\n -> afficher # compter ligne : permet de ccompter le nombre de ligne"
	"\n -> (s : send) file_message -s -c 10 -t 5 -m \"message\""
	"\n -> (r : receive) file_message -r -c 10 -t 5"
	"\n -> compiler \"nomprog.c\" -o \"nomexecutable\""
	"\n -> cas d'une commande non disponible"
	"\n");
}

int semaphore
