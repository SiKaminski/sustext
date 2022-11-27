#pragma once
#ifndef _SUSTEXT_KEYS_H
#define _SUSTEXT_KEYS_H
#define CTRL_KEY(k) ((k) & 0x1F)

namespace Sustext 
{
    enum Key : int {
        esc         = 27,
        backspace   = 127,
        arrowLeft   = 1000,
        arrowRight,
        arrowUp,
        arrowDown,
        del,
        home,
        end,
        pageUp,
        pageDown,
        
        escapeSequence  = '\x1b',
        carriageRet     = '\r',

        ctrl_q = CTRL_KEY('q'),
        ctrl_s = CTRL_KEY('s'),
        ctrl_h = CTRL_KEY('h'),
        ctrl_f = CTRL_KEY('f'),
        ctrl_l = CTRL_KEY('l'),
    };

}

#endif // _SUSTEXT_KEYS_H
