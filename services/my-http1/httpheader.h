#ifndef HTTPHEADER_H_
#define HTTPHEADER_H_

typedef struct HTTPREQUEST
{
    int size;
    int cap;
    char **col;
    char *body;
    int bodysize;
} HTTPREQUEST;

extern HTTPREQUEST *InitHeaders();
extern void DestroyHeaders(HTTPREQUEST *header);

extern int AddHeader(HTTPREQUEST *header, const char *text);

extern int SetBody(HTTPREQUEST *header, const char *body);

extern void Write(HTTPREQUEST *req, int fd);

#endif