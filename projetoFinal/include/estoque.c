
#include "carta.h"
#include "jogo.h"
#include "raylib.h"
#include <stdlib.h>

void renderizaCartasEstoque(void *info, void *jogoVar) {
  Carta *carta = (Carta *)info;
  Jogo *jogo = (Jogo *)jogoVar;

  // Caso a carta renderizada não seja a que está em movimento
  if (jogo->cartaEmMovimento != carta)
    renderizaCarta(info, jogoVar);

  if (carta->viradaParaBaixo)
    jogo->estoqueTopo = carta;
  else
    jogo->descarteTopo = carta;
}

void renderizaEstoque(Jogo *jogo) {
  DrawTexture(jogo->texturas.texturaEstoque, ESTOQUE_OFFSET_X, ESTOQUE_OFFSET_Y, WHITE);

  jogo->estoqueTopo = NULL;
  percorrePilhaReversoGEnc(jogo->estoque, renderizaCartasEstoque, jogo);
  jogo->descarteTopo = NULL;
  percorrePilhaReversoGEnc(jogo->descarte, renderizaCartasEstoque, jogo);

  Vector2 mousePos = GetMousePosition();

  // Verifica um clique no estoque quando nao tem nenhuma carta pra virar
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, ESTOQUE_OFFSET)) {
    if (vaziaPilhaGEnc(jogo->estoque)) {
      while (!vaziaPilhaGEnc(jogo->descarte)) {
        Carta *movimento = desempilhaPilhaGEnc(jogo->descarte);
        movimento->viradaParaBaixo = true;
        movimento->coordsMesa.x = 0;
        empilhaPilhaGEnc(jogo->estoque, movimento);
      }
      jogo->descarteTopo = NULL;
    }
  }

  // Verifica o clique na pilha de compra pra virar uma carta
  if (jogo->estoqueTopo && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, jogo->estoqueTopo->coordsMesa)) {
    jogo->estoqueTopo->viradaParaBaixo = false;
    jogo->estoqueTopo->coordsMesa.x = 150;
    Carta *movimento = desempilhaPilhaGEnc(jogo->estoque);
    empilhaPilhaGEnc(jogo->descarte, movimento);
  }

  // Verifica o clique pra arrastar alguma carta da pilha de descarte
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && jogo->descarteTopo && CheckCollisionPointRec(mousePos, jogo->descarteTopo->coordsMesa)) {
    if (jogo->cartaEmMovimento == NULL) {
      jogo->cartaEmMovimento = jogo->descarteTopo;
      jogo->cartaEmMovimento->posicaoAnterior = Rectangle2Vector(jogo->cartaEmMovimento->coordsMesa);
    }
  }
}