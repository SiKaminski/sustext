#if defined(__DATA_HPP) || defined(__EDITOR_HPP) || defined(__TERMINAL_HPP) || defined(__FILEHANDLER_HPP)
    #define EXTERN
    EXTERN EditorConfig E;
#else
    #define EXTERN extern
#endif // __DATA_HPP
