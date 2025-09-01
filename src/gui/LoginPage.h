#ifndef LOGINPAGE_H
#define LOGINPAGE_H
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class LoginPage : public QWidget {
    Q_OBJECT
public:
    explicit LoginPage(QWidget *parent = nullptr);

signals:
    void requestShowUserArea();
    void requestShowAdminArea();

private:
    QVBoxLayout* layout;
    QPushButton* areaUtente;
    QPushButton* areaAdmin;
    void setupStyles();

};

#endif // LOGINPAGE_H
