(defun print-matrix (matrix &optional (chars 3) stream)
  ;; Предполагаем, что требуется
  ;;  3 знака по умолчанию на каждый элемент,
  ;;  6 знаков на #2A и скобки.
  (let ((*print-right-margin* (+ 6 (* (1+ chars) ; плюс пробел
                                      (array-dimension matrix 1)))))
    (pprint matrix stream)
    (values)))

(defun spiral-matrix (n)
    (let ((matrix (make-array (list n n)))
         (el 1))
    
        (dotimes (i (ceiling n 2))
              (loop for j upfrom i to (- n i 1)
                  do(setf (aref matrix i j) el)
                    (setf el (1+  el))
              )
              (loop for j upfrom (+ i 1) to (- n i 1)
                  do(setf (aref matrix j (- n i 1)) el)
                    (setf el (1+  el))
              )
              (loop for j downfrom (- n i 2) to i
                  do(setf (aref matrix (- n i 1) j) el)
                    (setf el (1+  el))
              )
              (loop for j downfrom (- n i 2) to (+ i 1)
                  do(setf (aref matrix j i) el)
                    (setf el (1+  el))
              )
        )
    
        matrix
    )
)