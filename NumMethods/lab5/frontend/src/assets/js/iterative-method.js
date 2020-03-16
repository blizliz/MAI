function matrixNorm(A) {
  let norm = 0;
  for (let i = 0; i < A.length; i++) {
    let sum = 0;
    for (let j = 0; j < A.length; j++) {
      sum += Math.abs(A[i][j]);
    }
    if (sum > norm) {
      norm = sum;
    }
  }
  return norm;
}

function swapMatrixLines(A, i, j) {
  const tmp = A[i];
  A[i] = A[j];
  A[j] = tmp;
}

function swapItemsVector(v, i, j) {
  const tmp = v[i];
  v[i] = v[j];
  v[j] = tmp;
}

function fillMatrix(dim, value) {
  const matrix = []
  for (let i = 0; i < dim; i++) {
    matrix[i] = Array(dim).fill(value);
  }
  return matrix;
}

function findEquivalentSystem(A, b) {
  var equivlent = {
    'Alpha': Array,
    'beta': Array,
    'equivlent': function (n) {
      this.Alpha = fillMatrix(n, 0);
      this.beta = Array(n).fill(0);
    }
  }
  const n = A.length;

  equivlent.equivlent(n);

  for (let i = 0; i < n; i++) {
    if (A[i][i] === 0) {
      let swapFlag = false;
      for (let j = i + 1; j < n; j++) {
        if (A[j][i] !== 0) {
          swapMatrixLines(A, j, i);
          swapItemsVector(b, j, i);
          swapFlag = true;
          break;
        }
      }
      if (!swapFlag) {
        continue;
      }
    }

    equivlent.beta[i] = b[i] / A[i][i];
    for (let j = 0; j < n; j++) {
      if (i === j) {
        equivlent.Alpha[i][j] = 0;
      } else {
        equivlent.Alpha[i][j] = -A[i][j] / A[i][i];
      }
    }
  }

  return equivlent;
}

function diff(v1, v2) {
  const res = [];
  for (let i = 0; i < v1.length; i ++) {
    res[i] = v1[i] - v2[i];
  }
  return res;
}

function vectorNorm(v) {
  let norm = 0;
  for (let i = 0; i < v.length; i++) {
    if (Math.abs(v[i]) > norm) {
      norm = Math.abs(v[i]);
    }
  }
  return norm;

}

function iterativeMethod(A, b, eps) {
  const n = A.length;

  const equiv = findEquivalentSystem(A, b);
  const alphaNorm = matrixNorm(equiv.Alpha);
  let x = [];

  x = equiv.beta;
  if (alphaNorm < 1) {
    let endCond;
    let itNum = 1;
    do {
      const nextX = [];
      // Array(size).fill(0);
      for (let i = 0; i < n; i++) {
        let sum = 0;
        for (let j = 0; j < n; j++) {
          sum += equiv.Alpha[i][j] * x[j];
        }
        nextX[i] = equiv.beta[i] + sum;
      }
      const diffX = diff(nextX, x);
      endCond = alphaNorm / (1 - alphaNorm) * vectorNorm(diffX);

      x = nextX;
      ++itNum;
    } while (endCond > eps);
  } else if (alphaNorm === 1) {
    let endCond;
    let itNum = 1;
    do {
      const nextX = [];
      for (let i = 0; i < n; i++) {
        let sum = 0;
        for (let j = 0; j < n; j++) {
          sum += equiv.Alpha[i][j] * x[j];
        }
        nextX[i] = equiv.beta[i] + sum;
      }
      const diffX = diff(nextX, x);
      endCond = vectorNorm(diffX);

      x = nextX;
      ++itNum;
    } while (endCond > eps);
  }
  return x;
}
