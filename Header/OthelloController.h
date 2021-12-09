#ifndef _OTHELLOCONTROLLER_H
#define _OTHELLOCONTROLLER_H
class OthelloController {
public:
    // Delete possible copy approaches
    OthelloController(OthelloController &other) = delete;
    void operator=(const OthelloController &) = delete;

    static OthelloController* GetInstance();
    void PlayOthello();
private:
    OthelloController();
    static OthelloController* instance_;
};
#endif  // _OTHELLOCONTROLLER_H