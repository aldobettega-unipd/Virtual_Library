#ifndef USERPAGE_H
#define USERPAGE_H

#include "BasePage.h"


class UserPage : public BasePage
{
    Q_OBJECT

public:
    explicit UserPage(QWidget *parent = nullptr);

protected:
    void setupSpecificUI();
    void setupSpecificConnections();
};

#endif // USERPAGE_H
