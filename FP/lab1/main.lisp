(defun product (f a b)
  (cond ((= a b)  (funcall f b))
        ((> a b) 1)
        ((< a b)(* (funcall f a) (product f (1+ a) b)))))
