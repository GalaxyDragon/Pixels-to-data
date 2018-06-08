#ifndef CNT_H
#define CNT_H
#include <QApplication>
#include <QtWidgets>
#include <QObject>
#include <QWidget>
class cnt : public QObject
{
    Q_OBJECT
public:
    explicit cnt(QObject *parent = nullptr);
    ~cnt(){}
    QTableWidget* tab;
    QSpinBox* hi; QSpinBox* we; QSpinBox* cell; QRadioButton* bin; QRadioButton* hex;
    QWidget* mn;
    QTextEdit* text;
public slots:
    void table_resize();
    void cell_resize();
    void count();
    void copy();
};

#endif // CNT_H
