#pragma once
#ifndef _SUSTEXT_SIGNALS_HPP_
#define _SUSTEXT_SIGNALS_HPP_

namespace Sustext
{
    void SigIntHandler(int sig);
    void Cleanup();
}

#endif // _SUSTEXT_SIGNALS_HPP_
