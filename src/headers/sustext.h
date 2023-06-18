#pragma once
#ifndef _SUSTEXT_H_
#define _SUSTEXT_H_

namespace Sustext
{
    constexpr char* VERSION     {"v1.2.6"};
    //constexpr int TAB_STOP      {4};
    //constexpr int QUIT_TIMES    {1};

    void Initialize(int argc, char** argv);
    void Loop();
}

#endif // _SUSTEXT_H_
