#ifndef USERDETAILPAGE_H
#define USERDETAILPAGE_H

#include "BaseDetailPage.h"

class UserDetailPage : public BaseDetailPage
{
    Q_OBJECT
public:
    explicit UserDetailPage(QWidget* parent = nullptr);

protected:
    void setupSpecificUI() override;
    void setupSpecificConnections() override;

};

#endif // USERDETAILPAGE_H
