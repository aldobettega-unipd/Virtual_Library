#include "UserPage.h"
#include <QDebug>

UserPage::UserPage(QWidget *parent) : BasePage(parent)
{
    setupSpecificUI();
    setupSpecificConnections();
}

void UserPage::setupSpecificUI() {}
void UserPage::setupSpecificConnections() {}
void UserPage::handleMediaAction(Biblioteca* media) {}
