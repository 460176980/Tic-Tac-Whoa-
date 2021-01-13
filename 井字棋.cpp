#include<stdio.h> 
#include <stdlib.h>
int N=3;  //���̴�С
int M=3;  //���������(ʤ���������ٴ���1) 

 
typedef struct {
    int board[10][10];    // -1 = empty, 0 = O�����, 1 = X����� 
    int turn;           // O��������� 	 
} state;
state s;  //��ֱ��� 


/*��ʼ������״̬*/ 
void init(state* s) {
    int i, j;
    for (j = 0; j < N; j++)
        for (i = 0; i < N; i++)
            s->board[j][i] = -1;
    //���ȵ�O�������        
    s->turn = 0;
}


/*�ƶ�����*/ 
int move(state* s, int i, int j) {
	//�ڵ�i�У���j�л��塣���ж�����һλѡ�� 
    if (s->board[j][i] != -1)
        return 0;
        
    s->board[j][i] = s->turn++ % 2;//s->turn++��ת����һλѡ���� 
    return 1;
}

/*���������Ϸ*/ 
void human_TWO(state* s) {
    int c,line;
    char row;
    do {
    	//��������һ��λ�� 
        printf("player %c: ", "OX"[s->turn % 2]);
        getchar();
		scanf("%c%d",&row,&line); 
		c=(N-(row-'A')-1)*N+line;
		if(c < 1 || c > N*N){
        	printf("input error��please input number again\n");	
		}
    } while (!move(s, (c - 1) % N, (c - 1) / N)); //������λ�ò��Ϸ�ʱ�������� 
}

/*�����AI��һ����*/ 
void human_ONE(state* s,char choose) {
    int c,line;
    char row;
    
    do {
    	c=0;
    	//��������һ��λ�� 
    	if(choose=='Y'){

	    	if(s->turn % 2==0){
	    		printf("player: ");
	    		 //�ֶ�����һ���� 
				getchar();
				scanf("%c%d",&row,&line); 
				c=(N-(row-'A')-1)*N+line;
				if(c < 1 || c > N*N){
	        	   printf("input error��please input number again\n");	
				   continue;
				}
			} 
			else{
				 //�������һ����
				 c=rand()%(N*N);
				 while(1){
				 	//����Ѿ����ֲ��Ϸ�����ǰ�ƶ���� 
				 	if(c < 1 || c > N*N)
					 	c=(c+1)%(N*N);
					else
						break; //AI�º����� 
				 }
			}
		}
		else{
			if(s->turn % 2==1){
	    		printf("player: ");
	    		 //�ֶ�����һ���� 
				getchar();
				scanf("%c%d",&row,&line); 
				c=(N-(row-'A')-1)*N+line;
				if(c < 1 || c > N*N){
	        	   printf("input error��please input number again\n");	
				   continue;
				}
			} 
			else{
				 //�������һ����
				 c=rand()%(N*N);
				 while(1){
				 	//����Ѿ����ֲ��Ϸ�����ǰ�ƶ���� 
				 	if(c < 1 || c > N*N)
					 	c=(c+1)%(N*N);
					else
						break; //AI�º����� 
				 }
			}
		}

    } while (!move(s, (c - 1) % N, (c - 1) / N)); //������λ�ò��Ϸ�ʱ�������� 
}


//�������״�����Ӻ��ᡢ�����б��ͳ����������� 
int evaluate(const state* s) {
    int i,j;
    int temp;//��¼��ʱ��������� 
    
    //(1)�жϺ����Ƿ�����ʤ������ 
	for (i = 0; i < N; i++) {
		j=0;
		temp=1;
		while(j<N-1 && s->board[i][j]!=-1 && s->board[i][j]==s->board[i][j+1]){
			j++;
			temp++; 
		}
    	//�������ʤ������ 
		if(temp>=M)
			return (s->turn+1) % 2;//����ʤ���߱�� 
		
	}
	
	//(2)�ж�����ʤ������
	 for (j = 0; j < N; j++){
	 	i=0;
	 	temp=1;
	 	while(i<N-1&& s->board[i][j]!=-1  && s->board[i][j]==s->board[i+1][j]){
	 		temp++;
			i++; 	
		 } 

    	//�������ʤ������ 
		if(temp>=M)
			return (s->turn+1) % 2;//����ʤ���߱�� 

	 }
	 
	 //(3)�ж϶Խ���ʤ������
	 int temp_i,temp_j; 
	 for(i=0;i<N;i++){
	 	for(j=0;j<N;j++){
	 		
	 		//1.���ж���б�Խ������ 
	 		temp_i=i;temp_j=j;
	 		temp=1;
	 		while(temp_i<N-1 && temp_j<N-1&& s->board[temp_i][temp_j]!=-1  && s->board[temp_i][temp_j]==s->board[temp_i+1][temp_j+1]){
	 			temp++;
				temp_i++;
				temp_j++;	
			 } 
	 		if(temp>=M)
				return (s->turn+1) % 2;//����ʤ���߱�� 
			//2.���ж���б�Խ������ 
			temp_i=i;temp_j=j;
	 		temp=1;
	 		while(temp_i>0 && temp_j<N-1 && s->board[temp_i][temp_j]!=-1 && s->board[temp_i][temp_j]==s->board[temp_i-1][temp_j+1]){
	 			temp++;
				temp_i--;
				temp_j++; 	
			 } 
	 		if(temp>=M)
				return (s->turn+1) % 2;//����ʤ���߱�� 
		 }
	 } 
	 //(4)�ж�һ���Ƿ��������Ӷ��������ˣ�����ƽ��
	 int flag=1;
	 for(i=0;i<N;i++){
	 	for(j=0;j<N;j++){
	 		if(s->board[i][j]==-1){
	 			flag=0;
	 			break;
			 }
		 }
	 } 
	 if(flag)
	 	return 3; //ƽ�� 
    return -1;
}

/*չʾ����״��*/ 
void display(const state* s) {

    int i, j, k;
    char line[]="---"  ;//�������̻��� 
  
    for (j = 0; j < N; j++) {
    	printf(" %c  ",N-j-1+'A');
        for (i = 0; i < N; i++) {
            switch (s->board[j][i]) {
                case -1: printf("   ", j * N + i + 1); break;
                case  0: printf(" O "); break;
                case  1: printf(" X "); break;
            }
            if (i < N-1 )
                printf("|");
            else
                printf("\n");
        }
        //������Ҫ����һ�� 
        printf("    ",N-j+'A');
        if (j < N-1){
        	for(k=0;k<N-1;k++){
        		printf("%s+",line);
			}
			printf("%s\n",line);
		}
        else
            printf("\n");
    }
    printf("    ",j);
     for (j = 1; j <= N; j++){
		printf(" %2d ",j);
	 }
	printf("\n");
    
}

void human_human(){
	//(1)���ȳ�ʼ�����״̬ 
    init(&s);
    display(&s);
    while (s.turn < N*N) {
    	//(2)��ʼ���� 
        human_TWO(&s);
        //(3)Ȼ��չʾ��� S
        display(&s);
        //(4)���ж��Ƿ���Ӯ�ң�û������� 
        switch (evaluate(&s)) {
            case  0: printf("O win\n"); return ;
            case  1: printf("X win\n"); return ;
            case  3: printf("tie\n");return ;
        }
    } 
} 

//AI��������������� 
void human_AI(){
	//(1)���ȳ�ʼ�����״̬ 
    init(&s);
    //   ���ж��Ƿ����� 
    printf("first or last?(Y/N)"); 
	getchar();
	char choose;
	scanf("%c",&choose);
	//   �ж������Ƿ�Ϸ� 
	if(choose=='Y'||choose=='N'){
	    display(&s);
	    while (s.turn < N*N) {
	    	//(2)��ʼ���� 
	        human_ONE(&s,choose);
	        //(3)Ȼ��չʾ��� S
	        display(&s);
			//(4)���ж��Ƿ���Ӯ�ң�û������� 
	        switch (evaluate(&s)) {
	            case  0: if(choose=='Y') printf("player win\n");else  printf("AI win\n"); return ;
	            case  1: if(choose=='Y') printf("AI win\n");else  printf("player win\n"); return ;
	            case  3: printf("tie\n");return ;
	        }
	    }
	}
	else{
		printf("input error\b");
		return ;
	} 
	
	
}

//�������̴�С�Լ�ʤ������ 
void Setting(){
		printf("Game Setting\n");
		printf("1. N(default 4), input N 4.\n");
		printf("2. M(default 3), input M 3\n");
		char c;
		getchar(); 
		scanf("%c",&c);
		if(c=='N'){
			scanf("%d",&N);
		}
		else if(c=='M'){
			scanf("%d",&M);
		}
		else
			printf("input error��");
}


int main(){
	//��ʾ�˵�
	// �˵�
	while(1){
		int choose;
		printf("\n");
		printf("weclome to secure-Tic-Tac-Whoa!��\n");
		printf("1. start New Game (Human v. Human)\n");
		printf("2. start New Game (Human v. AI)\n");
		printf("3. Game Settings\n");
		printf("4. Exit Game\n");
		printf("Choose Option��");
		scanf("%d",&choose);
		
		switch(choose){
			case 1: human_human();continue; 
			case 2: human_AI();continue;		
			case 3: Setting();continue;
			case 4: return 0;
			default: printf("��������\n"); 
		}
	}

	return 0;
} 
