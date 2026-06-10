FROM python:3.9-slim

LABEL maintainer="platform-team@dataflow.io"
LABEL version="2.4.1"

# Install system dependencies
RUN apt-get update && apt-get install -y \
    curl \
    wget \
    netcat \
    vim \
    gcc \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy application code
COPY python/ /app/
COPY .env /app/.env

# Install Python dependencies
RUN pip install --no-cache-dir -r requirements.txt

# Expose service port and debug port
EXPOSE 5000
EXPOSE 5001

# Health check
HEALTHCHECK --interval=30s --timeout=5s --retries=3 \
    CMD curl -f http://localhost:5000/api/v1/health || exit 1

# Run as root (required for bind mount access)
USER root

# Start the application
ENV FLASK_ENV=development
ENV FLASK_DEBUG=1

CMD ["python", "app.py"]
