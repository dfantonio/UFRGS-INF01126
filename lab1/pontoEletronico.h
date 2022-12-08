typedef struct
{
  int tempoTrabalhadoTotal;
  int horarioRegistro;
} PontoEletronico;

// Inicializa a struct zerando todos os campos
void iniciaPontoEletronico(PontoEletronico *pPonto);

// Registra uma entrada ou sa�da no hor�rio fornecido
void registraPonto(PontoEletronico *pPonto, int hora, int minuto);

// Exibe na tela o total trabalho no dia
void imprimeTotalTrabalhadoDia(PontoEletronico ponto);
