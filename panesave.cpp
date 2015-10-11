#include "panesave.h"
#include<QDebug>

paneSave *paneSave::paneSaver = NULL;

paneSave::paneSave() {

}

paneSave::~paneSave() {

    delete widget;
    delete wlecomepane;
    delete wenshidu;
    delete door;
    delete animation;
    delete m_pBtnAnima;
    delete m_pProAnima;
    delete m_pSignalMapper;

}

paneSave *paneSave::instance() {
    if(paneSave::paneSaver == NULL) {
        paneSave::paneSaver = new paneSave;
    }
    return paneSave::paneSaver;
}
