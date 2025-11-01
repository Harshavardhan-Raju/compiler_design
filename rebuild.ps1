# Rebuild script with MSYS64 toolchain
# This script sets the correct PATH and rebuilds the compiler

Write-Host "============================================================" -ForegroundColor Cyan
Write-Host "  Rebuilding Compiler with MSYS64" -ForegroundColor Cyan
Write-Host "============================================================" -ForegroundColor Cyan
Write-Host ""

# Set PATH to use MSYS64 tools
$env:PATH = "C:\msys64\usr\bin;" + $env:PATH

Write-Host "Setting PATH to MSYS64..." -ForegroundColor Yellow
Write-Host "PATH: C:\msys64\usr\bin (prepended)" -ForegroundColor Gray
Write-Host ""

# Verify GCC
Write-Host "Checking GCC version..." -ForegroundColor Yellow
$gccVersion = & gcc --version 2>&1 | Select-Object -First 1
Write-Host "GCC: $gccVersion" -ForegroundColor Gray
Write-Host ""

# Clean previous build
Write-Host "Cleaning previous build..." -ForegroundColor Yellow
& make clean
if ($LASTEXITCODE -ne 0) {
    Write-Host "Warning: Clean failed (may be normal if no files to clean)" -ForegroundColor Yellow
}
Write-Host ""

# Build
Write-Host "Building compiler..." -ForegroundColor Yellow
& make
if ($LASTEXITCODE -ne 0) {
    Write-Host "ERROR: Build failed!" -ForegroundColor Red
    exit 1
}
Write-Host ""

# Verify binary
if (Test-Path ".\mycc.exe") {
    Write-Host "SUCCESS: mycc.exe built successfully!" -ForegroundColor Green
    $size = (Get-Item ".\mycc.exe").Length
    Write-Host "Binary size: $([math]::Round($size/1KB, 2)) KB" -ForegroundColor Gray
} else {
    Write-Host "ERROR: mycc.exe not found after build!" -ForegroundColor Red
    exit 1
}
Write-Host ""

# Test help flag
Write-Host "Testing -h flag..." -ForegroundColor Yellow
& .\mycc.exe -h
Write-Host ""

Write-Host "============================================================" -ForegroundColor Cyan
Write-Host "  Build Complete!" -ForegroundColor Green
Write-Host "============================================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "Next steps:" -ForegroundColor Yellow
Write-Host "  1. Run tests: .\run_tests.ps1" -ForegroundColor Gray
Write-Host "  2. Start Flask: python app1.py" -ForegroundColor Gray
Write-Host ""
