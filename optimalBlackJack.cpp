#include<iostream>
#include<stdlib.h>
using namespace std;

float p[29][29];
float pN[29][29]; 
float pi[29];
float pi1[29];
float htm[29][29]; //hit transition matrix
float faceCardProb;
float nonFaceCardProb;
int valueOfHand[29]={4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,12,13,14,15,16,17,18,19,20,21,22};
float win[29][11];
float loss[29][11];
char action[29][11];
char pairAction[10][11];
float doubleWin =0.0;
float doubleLoss =0.0;

int calculateNewHand (int currentHand, int cardDrawn)
{
	int newHand,currentHandValue, newHandValue;
	bool newHandisSoft, currentHandisSoft;
	
	
	if(currentHand <13)
	{
		currentHandValue = currentHand + 4;
		currentHandisSoft = false;
		newHandisSoft = false;
	}
	else if(currentHand > 17 && currentHand < 23)
	{
			currentHandValue = currentHand - 6;
			currentHandisSoft = true;
			newHandisSoft = true;
	}	
		
	newHandValue = currentHandValue + cardDrawn;
	
	if (cardDrawn  == 1)
	{
			newHandValue =  currentHandValue + 11;
			newHandisSoft = true;
		
		
	}
	if (newHandisSoft == true && newHandValue > 21)
	{
		newHandValue = newHandValue - 10;
		if(currentHandisSoft == true && cardDrawn == 1)
		{
			
				newHandisSoft = true;
				newHand = newHandValue + 6;
		}
		else
		{
			
				newHandisSoft = false;
				newHand = newHandValue - 4;	
		}
		
	}
	else if(newHandisSoft == false)
	{
			newHand = newHandValue - 4;
		
	}
	else if(newHandisSoft == true)
	{
			newHand = newHandValue + 6;
		
	}
	if(newHandValue > 21)
		newHand = 28;

return newHand;	
	
}


void calculateTransitionMatrix()
{
	float temp;
	for(int i =0 ; i <= 28; i++)
	{
		if( (i >= 13 && i <= 17) || (i>=23 && i<=27) || i ==28)
		{
			p[i][i]=1;
			for(int j=0; j <=28; j++)
			{
					if(i != j)
						p[i][j]= 0;
					
			}
				
		}
		else
		{
				for(int k = 1 ; k<=10; k++)
				{
					int j = calculateNewHand(i, k);
				
					if(k == 10)
						temp = faceCardProb;
					else
						temp = nonFaceCardProb;	
					
					p[i][j] = float(p[i][j] + temp);	
				}
		}
		
	}


}


void printTransitionMatrix()
{
	
		for(int i=0;i<=28;i++)
		{
			
			for(int j=0;j<=28;j++)
				cout<<p[i][j]<<" ";
			cout<<"\n";
		}
	
}

void copyTransitionMatrix()
{
	
		for(int i=0;i<=28;i++)
			for(int j=0;j<=28;j++)
				pN[i][j] = p[i][j];
	
}

void printFinalTransitionMatrix()
{
		for(int i=0;i<=28;i++)
		{
			
			for(int j=0;j<=28;j++)
				cout<<pN[i][j]<<" ";
			cout<<"\n";
		}
	
}

void calculateFinalP()
{		
		float tempP[29][29];
		for(int m=0;m<=20;m++)
		{
			 for(int i=0;i<= 28;i++)
			 {
				for(int j=0;j<= 28;j++)
				{
					tempP[i][j]=0.0;
					for(int k=0;k<= 28;k++)
					{
						tempP[i][j]=tempP[i][j]+pN[i][k]*p[k][j];
						
					}	
				}
			 }
			 for(int i=0;i<29;i++)
				for(int j =0;j<29;j++)
					pN[i][j]=tempP[i][j];
		}
		
	
}

void calculatePI(){
	
	float tempPI[1][29],tempPI1[1][29];
	for(int i=0;i<29;i++)
		tempPI[0][i] = pi[i];
	
	for(int i=0;i< 1;i++)
	 {
				for(int j=0;j<= 28;j++)
				{
					tempPI1[i][j]=0.0;
					for(int k=0;k<= 28;k++)
					{
						tempPI1[i][j]=tempPI1[i][j]+tempPI[i][k]*pN[k][j];
						
					}
				
						
				}
	 }
	
	for(int i=0;i<=28;i++)
		pi1[i]=tempPI1[0][i];
	}


int  getHand(int upCard, int nextCard){
	bool soft=false;
	int temp = 18,value;
	if(upCard == 1 && nextCard == 1)
		return temp;
	if(upCard == 1 || nextCard == 1)
		soft = true;
	
	
	value = upCard + nextCard;
	if(soft)
	{
		value = value + 6 + 10;
		return value ;	
	}
	else
	{
			value -=4;
			return value;
	}
	}


void calculateDealersStartingHand(int upCard)
{
		for(int i=0;i<=28;i++)
			pi[i] = 0.0;
		for(int i=1;i<=10;i++)
		{
		
			int hand = getHand(upCard, i);
			//cout<<"hand: "<<hand<<"\n";
			if(i==10)
				pi[hand] = faceCardProb;
			else
				pi[hand] = nonFaceCardProb;
		}
}


void printPI(){
	
	for(int i=0;i<=28;i++)
		cout<<pi1[i]<<" ";
	
}


int calculateNextHand(int hand, int upCard)
{
	int temp;
	if(hand == 17 || hand == 28)
	{
			temp = 28;
			return temp;
		
	}
	if(hand == 0 || hand == 1 || hand == 2 || hand == 3 || hand == 4 || hand ==5 || hand == 6)
	{
	if(upCard == 1)	
		temp = 21 + hand;
	else
		temp = hand + upCard;
	return temp;	
		
	}
	if(hand >= 7 && hand <17)
	{
	temp = hand + upCard;
	if(temp > 17)
		temp = 28;
	return temp;	
		
	}if(hand >17 && hand <27)
	{
	temp = hand + upCard;
	if(temp>27)
	{
		
			temp = upCard + hand - 20;
		
	}
	if(temp > 27)
		temp = 28;
	return temp;	
		
	}
	if(hand == 27)
	{
	temp = 7 + upCard;
	if(temp > 17)
	temp=28;
	return temp;	
		
	}
	
}

void makeHitTransitionMatrix(){
	
	for(int i=0;i<29;i++)
		for(int j=0;j<29;j++)
			htm[i][j]=0.0;
	
	for(int i=0;i<29;i++)
	{
		
			if(i==28)
				htm[i][i]=1;
			else
			{
				
				for(int k=1;k<=10;k++)
				{
					int j = calculateNextHand(i, k);
					
					if(k==10)
						htm[i][j] = htm[i][j] + faceCardProb;
					else
						htm[i][j] = htm[i][j] + nonFaceCardProb;
				}	
			}
	}
}


float getLoss(int upCard)
{
	if(upCard==1)
		return faceCardProb;
	else if(upCard == 10)
		return nonFaceCardProb;
	return 0.0;
}


void initializeC()
{
	for(int i=0;i<29;i++)
			for(int j=0;j<=10;j++)
			{
				win[i][j]=-1.0;
				loss[i][j]=-1.0;
			}
	for(int i=0;i<=10;i++)
		win[28][i]=0;
	
	for(int i=0;i<=10;i++)
		loss[28][i]=1;
	
	for(int k=1;k<=10;k++)
	{
			calculateDealersStartingHand(k);
			calculatePI();
			
			win[27][k]=0.0;
			loss[27][k]=0.0;
			win[17][k]=0.0;
			loss[17][k]=0.0;
		
			for(int i = 23;i<=26;i++)
				win[27][k] += pi1[i];
			
			for(int i = 13;i<17;i++)
				win[27][k] +=pi1[i];
		
			win[27][k] +=pi1[28];
			
			
			for(int i = 23;i<=26;i++)
				win[17][k] += pi1[i];
		
			for(int i = 13;i<=16;i++)
				win[17][k] +=pi1[i];
		
			win[17][k]+=pi1[28];
			
			
			loss[17][k] += getLoss(k);
			loss[27][k] += getLoss(k);
	 
	 }
	
	
	
	
	
}

float getdoubleDownReward(int currHand, int upCard)
{
	float e[1][29], tempPI[1][29], PI[29],pWin[29][1],pLoss[29][1],expP[29][1],standWin,standLoss;
	for(int i=0;i<29;i++)
		if(i== currHand)
			e[0][i]=1.0;
		else
			e[0][i]=0.0;
	
	for(int i=0;i< 1;i++)
	 {
			for(int j=0;j<= 28;j++)
			{
					tempPI[i][j]=0.0;
					for(int k=0;k<= 28;k++)
					{
						tempPI[i][j]=tempPI[i][j]+e[i][k]*htm[k][j];
						
					}	
				}
	 }
	
	for(int i=0;i<=28;i++)
		PI[i]=tempPI[0][i];
	
	calculateDealersStartingHand(upCard);
	calculatePI();
	for(int i=0;i<29;i++)
	{				
		standWin = pi1[28];
		for(int j =13; j<(valueOfHand[i]-4);j++)
			standWin += pi1[j];
		for(int j= 23; j<(valueOfHand[i]+6);j++)
			standWin +=pi1[j];
						
			standLoss = 0.0;
	
		for(int j=0;j<28;j++)
			if(valueOfHand[i]<valueOfHand[j])
				standLoss +=pi1[j];
		
		if(i == 17 || i == 27)
			standLoss += getLoss(upCard);
		
		if(i==28)
		{
			standLoss = 1;
			standWin = 0;	
							
		}
		
		pWin[i][0]=standWin;
		pLoss[i][0]=standLoss;
	}
	
	for(int i=0;i<29;i++)
	{
			expP[i][0] = pWin[i][0]-pLoss[i][0];
		
		
	}
	
	doubleWin =0.0;
	doubleLoss =0.0;
	float doubleReward =0.0;
	
	for(int i=0;i<29;i++)
		doubleReward += expP[i][0] * PI[i];
	
	for(int i=0;i<29;i++)
		doubleWin += pWin[i][0] * PI[i];
	
	for(int i=0;i<29;i++)
		doubleLoss += pLoss[i][0] * PI[i];
	
	return doubleReward; 
	
}


void addDouble()
{
	
		float doubleDownReward=0.0;
		//cout<<calculatedAction<<"\n";
		for(int i=0;i<=28;i++)
		{
				for(int k = 1; k<=10; k++)
				{
					// k is up card of dealer
					
					
					doubleDownReward = getdoubleDownReward(i, k);  
		
					if((2*doubleDownReward) >(win[i][k]-loss[i][k]) )
					{
							action[i][k]='D';
							win[i][k]=doubleWin;
							loss[i][k]=doubleLoss;
					}
					
					}
				}
			
	
	
}

void calculateStrategyChart()
{
		int calculatedAction = 290;
		float standWin, standLoss, hitWin,hitLoss,doubleDownReward;
		
		for(int i=0;i<29;i++)
			for(int j=0;j<11;j++)
				action[i][j]=' ';
		do 
		{
		for(int i=0;i<=28;i++)
		{
				for(int k = 1; k<=10; k++)
				{
					// k is up card of dealer
					calculateDealersStartingHand(k);
					calculatePI();
					
					standWin = pi1[28];
					for(int j =13; j<(valueOfHand[i]-4);j++)
							standWin += pi1[j];
					for(int j= 23; j<(valueOfHand[i]+6);j++)
							standWin +=pi1[j];
					
					standLoss = 0.0;
					
					for(int j=0;j<28;j++)
						if(valueOfHand[i]<valueOfHand[j])
								standLoss +=pi1[j];
					if(i == 17 || i == 27)
					standLoss += getLoss(k);
					if(i==28)
					{
					standLoss = 1;
					standWin = 0;	
						
					}
					
					hitWin=0.0;
					int flag =0;
					for(int j =0;j<29;j++)
						if(htm[i][j]!=0)
						{
								if(win[j][k]==-1)
								{
										flag =1;
										break;
								}
								else
								{
									hitWin +=htm[i][j]*win[j][k]; 
									
								}
						}
					
					hitLoss=0.0;
					
					for(int j =0;j<29;j++)
						if(htm[i][j]!=0)
						{
							if(loss[j][k]==-1)
							{
								flag =1;
								break;
							}
							else
							{
								hitLoss +=htm[i][j]*loss[j][k]; 
								
										
							}	
						}
					
					if(flag == 0 && action[i][k]==' ')
					{
						
						if((standWin-standLoss) > (hitWin-hitLoss))
						{
							action[i][k]='S';	
							win[i][k]=standWin;	
							loss[i][k]=standLoss;
							
						}
						else
						{	action[i][k]='H';	
							win[i][k]=hitWin;
							loss[i][k]=hitLoss;
							
						}
						calculatedAction--;
					}
				}
		}	
		}while(calculatedAction >0);
	
	addDouble();
	
}


void calculateAAPair()
{	float exp,standWin,standLoss;
	for(int j=1;j<=10;j++)
	{	// j is dealer up card
			exp=0.0,standWin=0.0,standLoss=0.0;
		for(int i=1;i<=10;i++) // i is next card
		{
				int temp = getHand(1,i);
				calculateDealersStartingHand(j);
				calculatePI();
		
				standWin = pi1[28];
				for(int k =13; k<(valueOfHand[temp]-4);k++)
							standWin += pi1[k];
				for(int k= 23; k<(valueOfHand[temp]+6);k++)
							standWin +=pi1[k];
					
					standLoss = 0.0;
					
				for(int k=0;k<28;k++)
						if(valueOfHand[temp]<valueOfHand[k])
								standLoss +=pi1[k];
				
				if(temp == 17 || temp == 27)
					standLoss += getLoss(j);
				if(temp==28)
				{
					standLoss = 1;
					standWin = 0;	
						
				}
				float tempWin = standWin - standLoss;
				if(i==10)
				{
					
				exp +=tempWin * faceCardProb;	
				}
				else
				{
					
				exp += tempWin * nonFaceCardProb;	
				}
		}
		exp *=2;
		
		float prevActionReward = (win[18][j]-loss[18][j]);
		
				if(action[18][j] == 'D')
					prevActionReward *=2; 
		
				if(prevActionReward < exp)
				{
					pairAction[9][j]='P';
					
					
				}
				else
				{
					pairAction[9][j]= action[18][j];
					
				}
		} 
}


void calculatePairAction(){
	
	float pH,ph[29],exp=0.0;
	for(int i=0;i<9;i++) // 2 to T
	{
			for(int j=1;j<=10;j++) // 2 to A dealers up card
			{
				if((i+2) == 10)
				{
						pH = faceCardProb;
				}
				else
				{
						pH = nonFaceCardProb;
						
				}	
				exp=0.0;
				for(int k =1;k<=10;k++)
				{
					int temp = getHand(i+2, k);
					
					if(i==8 && k==1)
					{
						exp += 1.5 * nonFaceCardProb;
						if(j==1)
							exp -=1.5*faceCardProb;
						if(j==10)
							exp -=1.5*nonFaceCardProb;
						
					}
					else
					{
						if(k!=(i+2))
						{
							
							float tempWin= win[temp][j] - loss[temp][j];
							if(action[temp][j]=='D')
								tempWin *=2;
							
								if(k==10)
								{
									exp += tempWin * faceCardProb;	
								}
								else
								{
									exp += tempWin * nonFaceCardProb;
								}		
						}
					}
					
				}
				
				exp = (float)((2 * exp )/(1- 2*pH));
				
				float prevActionReward = (win[(i+2)*2 - 4][j]-loss[(i+2)*2 -4][j]);
				if(action[(i+2)*2 - 4][j] == 'D')
					prevActionReward *=2; 
				
				
				if(prevActionReward < exp)
				{
					pairAction[i][j]='P';
				}
				else
				{
					pairAction[i][j]= action[(i+2)*2 - 4][j];
				}
			}	
	}		
}

int main(int argc, char **argv)
{
		float p1, p2;
		for(int i=0;i<29;i++)
			for(int j=0;j<29;j++)
			{
				
			p[i][j]= 0.0;
			pN[i][j]=0.0;
				
			}
		p1 = atof(argv[1]);
		faceCardProb = (float)(p1);
		nonFaceCardProb = (float)((1-faceCardProb )/9);
		
		calculateTransitionMatrix();
		
		copyTransitionMatrix();
		calculateFinalP();
		//printFinalTransitionMatrix();
		//calculateDealersStartingHand(2);
		//calculatePI();
		//printPI();
		makeHitTransitionMatrix();
		

		initializeC();
	
		calculateStrategyChart();
		calculatePairAction();
		
		calculateAAPair();
		
		//print complete policy
		for(int i=1;i<=15;i++)
		{
			cout<<i+4<<"\t";
				for(int j=2;j<=10;j++)
					cout<<action[i][j]<<" ";
				cout<<action[i][1];
			cout<<"\n";
			
		}
		for(int i=19;i<=26;i++)
		{
				cout<<"A"<<i-17<<"\t";
				for(int j=2;j<=10;j++)
					cout<<action[i][j]<<" ";
				cout<<action[i][1];
			cout<<"\n";
		}
		for(int i=0;i<9;i++)
		{
				cout<<i+2<<i+2<<"\t";
				for(int j=2;j<=10;j++)
					cout<<pairAction[i][j]<<" ";
				cout<<pairAction[i][1];
			cout<<"\n";
		}
		cout<<"AA\t";
		for(int j=2;j<=10;j++)
		{
			cout<<pairAction[9][j]<<" ";
			
			
		}
		cout<<pairAction[9][1];	
}
