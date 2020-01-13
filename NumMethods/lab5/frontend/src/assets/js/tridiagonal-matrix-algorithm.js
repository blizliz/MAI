function tridiagonalMatrixAlgorithm(a, b, c, d) {
  const p = [];
  const q = [];
  const p0 = -c[0] / b[0];
  const q0 = d[0] / b[0];
  p.push(p0);
  q.push(q0);

  var n = d.length;
  for (let i = 1; i < n; i++) {
    const pTmp = -c[i] / (b[i] + a[i] * p[i - 1]);
    p.push(pTmp);
    const qTmp = (d[i] - a[i] * q[i - 1]) / (b[i] + a[i] * p[i - 1]);
    q.push(qTmp);
  }
  --n;
  const x = [];
  x[n] = q[n];
  for (let i = n - 1; i >= 0; i--) {
    x[i] = p[i] * x[i + 1] + q[i];
  }

  return x;
}
