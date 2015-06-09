#ifndef SIMPLEYAML_HPP
#define SIMPLEYAML_HPP
#include <stddef.h>
#include <QString>
#include <QMap>

class YamlNode{
    YamlNode(QString info,YamlNode *last=NULL,YamlNode *next=NULL):
    m_last(last),
    m_next(next),
    m_info(info){
    }
    ~YamlNode(){
        delete m_last;
        delete m_next;
    }
    void setLast(YamlNode *last){m_last=last;}
    void setNext(YamlNode *next){m_next=next;}
    YamlNode* getLast(){return m_last;}
    YamlNode* getNext(){return m_next;}

    private:
    YamlNode    *m_last;
    YamlNode    *m_next;
    QString         m_info;
};

class SimpleYaml
{
public:
    SimpleYaml();
private:
    QMap<QString,YamlNode*> *m_mapNodes;
};

#endif // SIMPLEYAML_HPP
