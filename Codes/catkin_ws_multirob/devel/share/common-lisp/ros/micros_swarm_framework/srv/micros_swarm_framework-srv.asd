
(cl:in-package :asdf)

(defsystem "micros_swarm_framework-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "AppLoad" :depends-on ("_package_AppLoad"))
    (:file "_package_AppLoad" :depends-on ("_package"))
    (:file "AppUnload" :depends-on ("_package_AppUnload"))
    (:file "_package_AppUnload" :depends-on ("_package"))
    (:file "RTPDestroy" :depends-on ("_package_RTPDestroy"))
    (:file "_package_RTPDestroy" :depends-on ("_package"))
  ))