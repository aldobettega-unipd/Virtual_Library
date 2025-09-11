#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QCheckBox>
#include <QPushButton>

class SearchWidget : public QWidget
{
    Q_OBJECT
private:
    QFormLayout* formLayout;
    QLineEdit* searchBar;
    QPushButton* searchButton;
    QPushButton* resetButton;
    QWidget* filterBox;
    QCheckBox* box2000oggi;
    QCheckBox* box1900;
    QCheckBox* box1800;
    QCheckBox* box1700;
    QCheckBox* boxPrima1700;
    QLineEdit* linguaEdit;
    QLineEdit* genereEdit;
    QCheckBox* disponibileCheck;

    void setupUI();
    void setupConnections();

public:
    explicit SearchWidget(QWidget *parent = nullptr);

signals:
    void searchTextChanged(const QString& text);
    void filtersChanged(const QMap<QString, QVariant>& filters);

private slots:
    void onSearchButtonClicked();
    void onResetButtonClicked();

};

#endif // SEARCHWIDGET_H
