//
// Created by cwl on 19-2-11.
//

#ifndef STUDY_MYDOCKER_H
#define STUDY_MYDOCKER_H

#include <sys/wait.h>   // waitpid
#include <sys/mount.h>  // mount
#include <fcntl.h>      // open
#include <unistd.h>     // execv, sethostname, chroot, fchdir
#include <sched.h>      // clone

#define STACK_SIZE (512 * 512) // 定义子进程空间大小

namespace mydocker {

    void changeRunDir(std::string pathname) {
        chdir(pathname.c_str());
    }

}

#endif //STUDY_MYDOCKER_H
