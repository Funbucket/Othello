#ifndef _OTHELLOCONTROLLER_H
#define _OTHELLOCONTROLLER_H
class OthelloController {
public:
    static OthelloController* GetInstance();
    void PlayOthello();
private:
    OthelloController();
    static OthelloController* instance_;
};
#endif  // _OTHELLOCONTROLLER_H