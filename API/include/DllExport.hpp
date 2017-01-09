//
// Created by veyrie_f on 09/01/17.
//

#ifndef API_V2_DLLEXPORT_HPP
#define API_V2_DLLEXPORT_HPP

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#endif //API_V2_DLLEXPORT_HPP
