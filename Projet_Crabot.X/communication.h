#ifndef COMMUNICATION_H
#define	COMMUNICATION_H


#define SIZE_BUFFER_COM 100

void Init_Communication_RasPi(void);

void AnalyzeCommandFromPi (char b);
void SelectActionFromPi (void);
void SendDone(void);
void SendStart(void);
void SendEnd (void);
void SendFailAX12(void);
void SendTeam (int team);
void SendNum_Config (void);

void DetectSick(int channel);
void ReleaseSick (int channel);
void SendSick_Status(int val8);

void DetectUltrason(void);
void ReleaseUltrason(void);
void SendUltrason_Status(void);
void SendUrge(void);

int write(int handle, void *buffer, unsigned int len);
void Transmit_Char(char symbol);


#endif	/* COMMUNICATION_H */

