#pragma once
#ifndef _SUSTEXT_H
#define _SUSTEXT_H

namespace Sustext
{
    constexpr char* VERSION     {"v1.2.6"};
    constexpr int TAB_STOP      {4};
    constexpr int QUIT_TIMES    {1};

    void Initialize(int argc, char** argv);
}

#endif // _SUSTEXT_H
