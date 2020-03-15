#include "MessagePackage.h"

MessagePackage::MessagePackage(/* args */)
{
}

MessagePackage::~MessagePackage()
{
    // delete head;
    delete body;
    delete buffer;
}

int MessagePackage::package()
{
    buildHeader();
    buffer = new char[sizeof(head) + strlen(body)];
    memccpy(buffer, &head.start, NULL, 4);
    memccpy(&buffer[4], &head.version, NULL, 4);
    memccpy(&buffer[8], &head.comdId, NULL, 4);
    memccpy(&buffer[12], &head.seq, NULL, 4);
    memccpy(&buffer[16], &head.bodyLen, NULL, 4);

    //body
    memccpy(&buffer[20], body, NULL, strlen(body));

    slog(TAG, buffer, sizeof(buffer));
    return sizeof(head) + head.bodyLen;
}

void MessagePackage::buildHeader()
{
    //  memset(head, '0', 20);

    // //Version  4~8
    // const unsigned int verInt = getClientVersion();
    // memcpy( &head[4], &verInt , 4 );

    // //CMD ID  8~12
    // const unsigned int cmdId = getCmdId();
    // memcpy(&head[8], &cmdId , 4 );

    // //body length  16~20
    // const unsigned int bodyLen = strlen(body);
    // memcpy(&head[16], &bodyLen, 4 );

    head.start = 0x012;
    head.comdId = getCmdId();
    head.version = getClientVersion();
    head.seq = 0;
    head.bodyLen = strlen(body);

    slog(TAG, "headLen :", sizeof(head));
    slog(TAG, "bodyLen :", head.bodyLen);
    slog(TAG, "head version :", head.version);
    slog(TAG, body);
}

void MessagePackage::unPackage(struct Head *headTmp, char *bodyTmp)
{
    //set the data to Head
    memcpy(&head, headTmp, sizeof(Head));
    //设置body
    body = new char[headTmp->bodyLen];
    memcpy(body, bodyTmp, headTmp->bodyLen);
}

Head *MessagePackage::getHead()
{
    return &this->head;
}

void MessagePackage::setBody(char *mbody)
{
    body = new char[strlen(mbody)];
    memcpy(body, mbody, strlen(mbody));
}

char *MessagePackage::getBody()
{
    return this->body;
}

char *MessagePackage::getBuffer()
{
    return this->buffer;
}

Head *MessagePackage::checkPackageHead(char *origin)
{
    struct Head *head = (struct Head *)origin;
    if (head->start != 0)
    {
        return nullptr;
    }
    return (Head *)origin;
}