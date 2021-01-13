#include<stdio.h> 
#include <stdlib.h>
int N=3;  //棋盘大小
int M=3;  //最大连子数(胜利条件至少大于1) 

 
typedef struct {
    int board[10][10];    // -1 = empty, 0 = O号玩家, 1 = X号玩家 
    int turn;           // O号玩家优先 	 
} state;
state s;  //棋局变量 


/*初始化棋盘状态*/ 
void init(state* s) {
    int i, j;
    for (j = 0; j < N; j++)
        for (i = 0; i < N; i++)
            s->board[j][i] = -1;
    //首先到O号玩家走        
    s->turn = 0;
}


/*移动棋盘*/ 
int move(state* s, int i, int j) {
	//在第i行，第j列画棋。并判断是哪一位选手 
    if (s->board[j][i] != -1)
        return 0;
        
    s->board[j][i] = s->turn++ % 2;//s->turn++跳转到另一位选手了 
    return 1;
}

/*人类进行游戏*/ 
void human_TWO(state* s) {
    int c,line;
    char row;
    do {
    	//输入走哪一个位置 
        printf("player %c: ", "OX"[s->turn % 2]);
        getchar();
		scanf("%c%d",&row,&line); 
		c=(N-(row-'A')-1)*N+line;
		if(c < 1 || c > N*N){
        	printf("input error，please input number again\n");	
		}
    } while (!move(s, (c - 1) % N, (c - 1) / N)); //当输入位置不合法时重新输入 
}

/*人类和AI下一步棋*/ 
void human_ONE(state* s,char choose) {
    int c,line;
    char row;
    
    do {
    	c=0;
    	//输入走哪一个位置 
    	if(choose=='Y'){

	    	if(s->turn % 2==0){
	    		printf("player: ");
	    		 //手动输入一步棋 
				getchar();
				scanf("%c%d",&row,&line); 
				c=(N-(row-'A')-1)*N+line;
				if(c < 1 || c > N*N){
	        	   printf("input error，please input number again\n");	
				   continue;
				}
			} 
			else{
				 //随机输入一步棋
				 c=rand()%(N*N);
				 while(1){
				 	//如果已经数字不合法则向前移动检查 
				 	if(c < 1 || c > N*N)
					 	c=(c+1)%(N*N);
					else
						break; //AI下好了棋 
				 }
			}
		}
		else{
			if(s->turn % 2==1){
	    		printf("player: ");
	    		 //手动输入一步棋 
				getchar();
				scanf("%c%d",&row,&line); 
				c=(N-(row-'A')-1)*N+line;
				if(c < 1 || c > N*N){
	        	   printf("input error，please input number again\n");	
				   continue;
				}
			} 
			else{
				 //随机输入一步棋
				 c=rand()%(N*N);
				 while(1){
				 	//如果已经数字不合法则向前移动检查 
				 	if(c < 1 || c > N*N)
					 	c=(c+1)%(N*N);
					else
						break; //AI下好了棋 
				 }
			}
		}

    } while (!move(s, (c - 1) % N, (c - 1) / N)); //当输入位置不合法时重新输入 
}


//评估棋局状况，从横轴、纵轴和斜线统计最大连子数 
int evaluate(const state* s) {
    int i,j;
    int temp;//记录临时最大连子数 
    
    //(1)判断横轴是否满足胜利条件 
	for (i = 0; i < N; i++) {
		j=0;
		temp=1;
		while(j<N-1 && s->board[i][j]!=-1 && s->board[i][j]==s->board[i][j+1]){
			j++;
			temp++; 
		}
    	//如果满足胜利条件 
		if(temp>=M)
			return (s->turn+1) % 2;//返回胜利者编号 
		
	}
	
	//(2)判断纵轴胜利条件
	 for (j = 0; j < N; j++){
	 	i=0;
	 	temp=1;
	 	while(i<N-1&& s->board[i][j]!=-1  && s->board[i][j]==s->board[i+1][j]){
	 		temp++;
			i++; 	
		 } 

    	//如果满足胜利条件 
		if(temp>=M)
			return (s->turn+1) % 2;//返回胜利者编号 

	 }
	 
	 //(3)判断对角线胜利条件
	 int temp_i,temp_j; 
	 for(i=0;i<N;i++){
	 	for(j=0;j<N;j++){
	 		
	 		//1.先判断左斜对角线情况 
	 		temp_i=i;temp_j=j;
	 		temp=1;
	 		while(temp_i<N-1 && temp_j<N-1&& s->board[temp_i][temp_j]!=-1  && s->board[temp_i][temp_j]==s->board[temp_i+1][temp_j+1]){
	 			temp++;
				temp_i++;
				temp_j++;	
			 } 
	 		if(temp>=M)
				return (s->turn+1) % 2;//返回胜利者编号 
			//2.再判断右斜对角线情况 
			temp_i=i;temp_j=j;
	 		temp=1;
	 		while(temp_i>0 && temp_j<N-1 && s->board[temp_i][temp_j]!=-1 && s->board[temp_i][temp_j]==s->board[temp_i-1][temp_j+1]){
	 			temp++;
				temp_i--;
				temp_j++; 	
			 } 
	 		if(temp>=M)
				return (s->turn+1) % 2;//返回胜利者编号 
		 }
	 } 
	 //(4)判断一下是否所有棋子都被堆满了，是则平局
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
	 	return 3; //平局 
    return -1;
}

/*展示棋盘状况*/ 
void display(const state* s) {

    int i, j, k;
    char line[]="---"  ;//横轴棋盘绘制 
  
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
        //这里需要调整一下 
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
	//(1)首先初始化棋局状态 
    init(&s);
    display(&s);
    while (s.turn < N*N) {
    	//(2)开始下棋 
        human_TWO(&s);
        //(3)然后展示棋局 S
        display(&s);
        //(4)并判断是否有赢家，没有则继续 
        switch (evaluate(&s)) {
            case  0: printf("O win\n"); return ;
            case  1: printf("X win\n"); return ;
            case  3: printf("tie\n");return ;
        }
    } 
} 

//AI采用随机数生成棋 
void human_AI(){
	//(1)首先初始化棋局状态 
    init(&s);
    //   再判断是否先手 
    printf("first or last?(Y/N)"); 
	getchar();
	char choose;
	scanf("%c",&choose);
	//   判断输入是否合法 
	if(choose=='Y'||choose=='N'){
	    display(&s);
	    while (s.turn < N*N) {
	    	//(2)开始下棋 
	        human_ONE(&s,choose);
	        //(3)然后展示棋局 S
	        display(&s);
			//(4)并判断是否有赢家，没有则继续 
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

//设置棋盘大小以及胜利条件 
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
			printf("input error！");
}


int main(){
	//显示菜单
	// 菜单
	while(1){
		int choose;
		printf("\n");
		printf("weclome to secure-Tic-Tac-Whoa!！\n");
		printf("1. start New Game (Human v. Human)\n");
		printf("2. start New Game (Human v. AI)\n");
		printf("3. Game Settings\n");
		printf("4. Exit Game\n");
		printf("Choose Option：");
		scanf("%d",&choose);
		
		switch(choose){
			case 1: human_human();continue; 
			case 2: human_AI();continue;		
			case 3: Setting();continue;
			case 4: return 0;
			default: printf("输入有误\n"); 
		}
	}

	return 0;
} 
