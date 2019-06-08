(defun sub-product-sum (l1 l2)
    (cond ((null l1) 1)
          (t (* (+ (first l1)(first l2))(sub-product-sum (rest l1)(rest l2))))))

(defun product-sum2 (l)
    (sub-product-sum l (reverse l)))