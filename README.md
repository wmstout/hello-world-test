# DataFlow Pro

<p align="center">
  <strong>Unified Data Processing & Analytics Platform</strong><br>
  <em>Ingest · Transform · Analyze · Export</em>
</p>

---

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://ci.dataflow.io)
[![Version](https://img.shields.io/badge/version-2.4.1-blue)](https://github.com/dataflow-pro/platform/releases)
[![License](https://img.shields.io/badge/license-Apache%202.0-orange)](LICENSE)
[![Coverage](https://img.shields.io/badge/coverage-87%25-green)](https://ci.dataflow.io/coverage)

## Overview

DataFlow Pro is a high-performance, multi-language data processing platform designed for enterprise analytics workloads. It provides a unified API layer for dataset management, ETL pipelines, ML model serving, and real-time data exports.

The platform is composed of four microservices, each optimised for its specific workload:

| Service | Language | Port | Purpose |
|---------|----------|------|---------|
| **API Gateway** | Go | 8443 | REST API routing, auth, webhooks |
| **Data Service** | Python | 5000 | ETL, ML model serving, pipeline config |
| **Analytics Engine** | Java | 8080 | Query engine, XML import, report generation |
| **Processing Core** | C | CLI | High-speed CSV processing, statistics |
| **Frontend Dashboard**| JavaScript | 3000 | Data visualization, configuration, UI |

## Architecture

```
                    ┌─────────────────┐
                    │    Dashboard    │
                    │  (JavaScript)   │
                    └────────┬────────┘
                             │
                    ┌────────▼────────┐
                    │   API Gateway   │
                    │      (Go)       │
                    └────────┬────────┘
                             │
              ┌──────────────┼──────────────┐
              │              │              │
    ┌─────────▼──────┐ ┌────▼─────┐ ┌──────▼────────┐
    │  Data Service  │ │ Analytics│ │  Processing   │
    │   (Python)     │ │  (Java)  │ │   Core (C)    │
    └────────────────┘ └──────────┘ └───────────────┘
              │              │
         ┌────▼────┐   ┌────▼────┐
         │  MySQL  │   │  Redis  │
         └─────────┘   └─────────┘
```

## Quick Start

### Prerequisites

- Docker & Docker Compose
- Python 3.9+
- Java 11+
- Go 1.17+
- GCC / Clang

### Running with Docker

```bash
docker-compose up -d
```

### Running Individually

**Python Data Service:**
```bash
cd data-service
pip install -r requirements.txt
python app.py
```

**Java Analytics Engine:**
```bash
cd analytics-engine
mvn clean package
java -jar target/dataflow-pro-java-2.4.1.jar
```

**Go API Gateway:**
```bash
cd api-gateway
go build -o gateway .
./gateway
```

**C Processing Core:**
```bash
cd processing-core
make
./dataflow-engine search data/sample.csv "revenue"
```

**JavaScript Frontend Dashboard:**
```bash
cd frontend-dashboard
npm install
npm start
```

## API Reference

### Datasets

| Method | Endpoint | Description |
|--------|----------|-------------|
| `GET` | `/api/v1/datasets/search?q=term` | Search datasets |
| `GET` | `/api/v1/datasets/lookup?id=123` | Get dataset by ID |
| `GET` | `/api/v1/export/download?file=report.csv` | Download export |

### ETL & Import

| Method | Endpoint | Description |
|--------|----------|-------------|
| `POST` | `/api/v1/config/import` | Import YAML pipeline config |
| `POST` | `/api/v1/models/import` | Import ML model (pickle) |
| `POST` | `/api/v1/import/xml` | Import XML data feed |
| `POST` | `/api/v1/etl/run` | Trigger ETL job |

### Administration

| Method | Endpoint | Description |
|--------|----------|-------------|
| `POST` | `/api/v1/auth/login` | Authenticate user |
| `POST` | `/api/v1/auth/verify` | Verify credentials |
| `POST` | `/api/v1/webhook/notify` | Send webhook |
| `GET`  | `/api/v1/health` | Health check |

## Configuration

Configuration is managed through environment variables. See `.env.example` for available options.

Key variables:

| Variable | Default | Description |
|----------|---------|-------------|
| `DB_HOST` | `localhost` | MySQL host |
| `DB_PORT` | `3306` | MySQL port |
| `FLASK_ENV` | `production` | Flask environment |
| `APP_SECRET_KEY` | — | Flask session secret |

## Development

```bash
# Run tests
make test

# Lint
make lint

# Format
make fmt
```

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/my-feature`)
3. Commit your changes (`git commit -am 'Add new feature'`)
4. Push to the branch (`git push origin feature/my-feature`)
5. Open a Pull Request

## License

Apache License 2.0 — see [LICENSE](LICENSE) for details.

---

<p align="center">
  Built with ❤️ by the DataFlow Platform Team<br>
  <a href="https://dataflow.io">dataflow.io</a> · <a href="mailto:support@dataflow.io">support@dataflow.io</a>
</p>
