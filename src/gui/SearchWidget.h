#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QCheckBox>

class SearchWidget : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout* layout;
    QLineEdit* searchBar;
    QWidget* filterBox;

    // Filtri
    QCheckBox* box2000oggi;
    QCheckBox* box1900;
    QCheckBox* box1800;
    QCheckBox* box1700;
    QCheckBox* boxPrima1700;
    QLineEdit* autoreEdit;
    QLineEdit* genereEdit;
    QCheckBox* disponibileCheck;

public:
    explicit SearchWidget(QWidget *parent = nullptr);
    void setupUI();
    void setupConnections();

signals:
    void searchTextChanged(const QString& text);
    void filtersChanged(const QMap<QString, QVariant>& filters);

private slots:
    void onSearchTextChanged(const QString& text);
    void onFiltersChanged();

};

#endif // SEARCHWIDGET_H
